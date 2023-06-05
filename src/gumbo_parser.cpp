#include "gumbo_parser.hpp"	// Current header

namespace se {

namespace {

GumboNode* findHeadNode(GumboNode* a_node)
{
    const GumboVector* root_children = &a_node->v.element.children;
    GumboNode* head = nullptr;

    auto rootSize = root_children->length;
    for (unsigned int i = 0; i < rootSize; ++i) {
        GumboNode* child = static_cast<GumboNode*>(root_children->data[i]);

        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) {
            head = child;
            break;
        }
    }
    return head;
}

std::string recursiveGetLinks(GumboNode* a_node)
{
    if (a_node->type != GUMBO_NODE_ELEMENT) {
        return "";
    }

    std::string buff = "";
    std::string space = " ";
    GumboAttribute* href;

    if (a_node->v.element.tag == GUMBO_TAG_A && (href = gumbo_get_attribute(&a_node->v.element.attributes, "href"))) {
        buff += space + href->value;
    }

    GumboVector* children = &a_node->v.element.children;
    auto size = children->length;

    for (unsigned int i = 0; i < size; ++i) {
        buff += recursiveGetLinks(static_cast<GumboNode*>(children->data[i]));
    }

    return buff;
}

std::string recursiveGetParagraphsText(GumboNode* a_node)
{
    std::string paragraphText = "";
    GumboVector* children = &a_node->v.element.children;
    auto size = children->length;

    if (a_node->type == GUMBO_NODE_ELEMENT) {
        if (a_node->v.element.tag == GUMBO_TAG_P) {
            for (unsigned int i = 0; i < size; ++i) {
                GumboNode* childNode = static_cast<GumboNode*>(children->data[i]);
                if (childNode->type == GUMBO_NODE_TEXT) {
                    paragraphText += childNode->v.text.text;
                }
            }
        }
        else {
            for (unsigned int i = 0; i < size; ++i) {
                GumboNode* childNode = static_cast<GumboNode*>(children->data[i]);
                paragraphText += recursiveGetParagraphsText(childNode);
            }
        }
    }

    return paragraphText;
}

} // empty namespace for static functions

GumboParser::GumboParser()
: m_extractor()
, m_root()
{}

void GumboParser::parse(const std::ostringstream& a_html)
{
    m_extractor = gumbo_parse(a_html.str().c_str());
    m_root = m_extractor->root;
}

void GumboParser::freeParse()
{
    gumbo_destroy_output(&kGumboDefaultOptions, m_extractor);
}

std::string GumboParser::getTitle()
{
    if(m_root->type != GUMBO_NODE_ELEMENT || m_root->v.element.children.length < 2) {
        return nullptr;
    }

    GumboNode* head = findHeadNode(m_root);
    if(head == nullptr) {
        return nullptr;
    }

    GumboVector* head_children = &head->v.element.children;
    auto headChildrenSize = head_children->length;

    for (unsigned int i = 0; i < headChildrenSize; ++i) {
        GumboNode* child = static_cast<GumboNode*>(head_children->data[i]);
        if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE) {
            if (child->v.element.children.length != 1) {
                return "<empty title>";
            }

            GumboNode* title_text = static_cast<GumboNode*>(child->v.element.children.data[0]);
            if(title_text->type != GUMBO_NODE_TEXT && title_text->type != GUMBO_NODE_WHITESPACE) {
                return "<empty title>";
            }

            return title_text->v.text.text;
        }
    }

    return "<no title found>";
}

std::string GumboParser::getLinks()
{
    return recursiveGetLinks(m_root);
}

std::string GumboParser::getParagraphsText()
{
    return recursiveGetParagraphsText(m_root);
}

} // namespace se
