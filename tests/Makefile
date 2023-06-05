TESTS = all crawl curlpp_downloader data_base gumbo_parser json_file_reader link_data query search string_utils validator
TESTS += web_page word_index

check:
	$(foreach T, $(TESTS), $(MAKE) -C $(T) check;)

clean:
	$(foreach T, $(TESTS), $(MAKE) -C $(T) clean;)
