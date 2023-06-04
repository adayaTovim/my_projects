#include "mu_test.h"

#include <thread>
#include <optional>
#include <algorithm>
#include <vector>
#include <array>

#include "waitable_queue.hpp"

class Dog {
public:
    enum Color {
        WHITE,
        BLACK,
        BROWN, 
        ORANGE
    };

    explicit Dog(size_t a_id, enum Color a_color);
    bool operator<(const Dog& a_other) const;
    size_t getId() const;
    enum Color getColor() const;

private:
    size_t m_id;
    enum Color m_color;
};

Dog::Dog(size_t a_id, enum Color a_color) 
: m_id(a_id)
, m_color(a_color)
{
}

size_t Dog::getId() const
{
    return m_id;
}

enum Dog::Color Dog::getColor() const
{
    return m_color;
}

bool Dog::operator<(const Dog& a_other) const
{
    return getId() > a_other.getId();
}

bool dogComparator(const Dog& a_dog1, const Dog& a_dog2) {
    if (a_dog1.getColor() != a_dog2.getColor()) {
        return a_dog1.getColor() < a_dog2.getColor();
    }
    return a_dog1.getId() < a_dog2.getId();
}

BEGIN_TEST(FIFOwithOneThread)
    using namespace advcpp;
    constexpr size_t N = 1000;
    WaitableQueue<Dog> q(N);
    for(size_t i = 0; i < N; ++i) {
        Dog dog(i, Dog::Color::BROWN); 
        q.enqueue(dog);
    }

    ASSERT_EQUAL(q.size(), N);
    
    for(size_t i = 0; i < N; ++i) {
        Dog removedDog(i, Dog::Color::BROWN);
        q.dequeue(removedDog);
        if(removedDog.getId() == i && removedDog.getColor() == Dog::Color::BROWN) {
            ASSERT_PASS();
        }
    }
    ASSERT_EQUAL(q.size(),0);

END_TEST


BEGIN_TEST(FIFOwithOneConsumerOneProducer)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;

    std::thread producter([&q]() {
        for(size_t i = 0; i < count; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    std::thread consumer([&q, &is_fifo]() {
        for(size_t i = 0; i < count; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);
            if (removedDog.getId() != i) {
                is_fifo = false;
                break;
            }
        }       
    });
    
    producter.join();
    consumer.join();
    ASSERT_THAT(is_fifo);
    ASSERT_EQUAL(q.size(), 0);

END_TEST

BEGIN_TEST(FIFOwithTwoProducersOneConsumer)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;

    std::thread producer1([&q]() {
        for(size_t i = 0; i < count/2; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    std::thread producer2([&q]() {
        for(size_t i = 0; i < count/2; ++i) {
            q.enqueue(Dog(i, Dog::WHITE));
        }   
    });

    size_t blackCounter = 0;
    size_t whiteCounter = 0;

    std::thread consumer([&q, &is_fifo, &blackCounter, &whiteCounter]() {
        for(size_t i = 0; i < count; ++i) {
            
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if(removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() != blackCounter) {
                    is_fifo = false;
                    break;
                }
                ++blackCounter;
            }
            
            if(removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() != whiteCounter) {
                    is_fifo = false;
                    break;
                }
                ++whiteCounter;
            }
        }
    });
    
    producer1.join();
    producer2.join();
    consumer.join();

    ASSERT_THAT(is_fifo);
    ASSERT_EQUAL(q.size(), 0);

END_TEST

BEGIN_TEST(FIFOwithOneProducerTwoConsumers)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;

    std::thread producer([&q]() {
        for(size_t i = 0; i < count; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    size_t Counter1 = 0;
    size_t Counter2 = 0;
    std::vector<Dog> dogsCheck1;
    std::vector<Dog> dogsCheck2;

    std::thread consumer1([&q, &is_fifo, &Counter1, &dogsCheck1]() {
        for(size_t i = 0; i < count/2; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if(removedDog.getId() < Counter1) {
                is_fifo = false;
                break;
            }
            Counter1 = removedDog.getId();
            dogsCheck1.push_back(removedDog);
        }
    });
    
    std::thread consumer2([&q, &is_fifo, &Counter2,  &dogsCheck2]() {
        for(size_t i = 0; i < count/2; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if(removedDog.getId() < Counter2) {
                is_fifo = false;
                break;
            }
            Counter2 = removedDog.getId();
            dogsCheck2.push_back(removedDog);
        }
    });

    producer.join();
    consumer1.join();
    consumer2.join();

    dogsCheck1.insert(dogsCheck1.end(), dogsCheck2.begin(), dogsCheck2.end());
    std::sort(dogsCheck1.begin(), dogsCheck1.end(), [](const Dog& a, const Dog& b) {
        return a.getId() < b.getId();
    });
    for(size_t i = 0; i < dogsCheck1.size(); ++i) {
        ASSERT_EQUAL(dogsCheck1[i].getId(), i);
        ASSERT_EQUAL(dogsCheck1[i].getColor(), Dog::BLACK);
    }

    ASSERT_THAT(is_fifo);
    ASSERT_EQUAL(q.size(), 0);

END_TEST

BEGIN_TEST(FIFOwithFourProducersFourConsumers)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;
    auto is_complete = true;
    
    std::thread producer1([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    std::thread producer2([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::WHITE));
        }   
    });

    std::thread producer3([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::BROWN));
        }    
    });

    std::thread producer4([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::ORANGE));
        }   
    });

    size_t counter1[4] = {0};
    size_t counter2[4] = {0};
    size_t counter3[4] = {0};
    size_t counter4[4] = {0};

    std::vector<Dog> dogsCheck1;
    std::vector<Dog> dogsCheck2;
    std::vector<Dog> dogsCheck3;
    std::vector<Dog> dogsCheck4;

    std::thread consumer1([&q, &is_fifo, &counter1, &dogsCheck1]() {
        for(size_t i = 0; i < count/4; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if (removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::BROWN) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::ORANGE) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }

            counter1[removedDog.getColor()] = removedDog.getId();
            dogsCheck1.push_back(removedDog);
        }
    });
    
    std::thread consumer2([&q, &is_fifo, &counter2, &dogsCheck2]() {
        for(size_t i = 0; i < count/4; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if (removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::BROWN) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::ORANGE) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }

            counter2[removedDog.getColor()] = removedDog.getId();
            dogsCheck2.push_back(removedDog);
        }
    });

    std::thread consumer3([&q, &is_fifo, &counter3, &dogsCheck3]() {
        for(size_t i = 0; i < count/4; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if (removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::BROWN) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::ORANGE) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }

            counter3[removedDog.getColor()] = removedDog.getId();
            dogsCheck3.push_back(removedDog);
        }
    });
    
    std::thread consumer4([&q, &is_fifo, &counter4, &dogsCheck4]() {
    for(size_t i = 0; i < count/4; ++i) {
        Dog removedDog(i, Dog::Color::BROWN);
        q.dequeue(removedDog);

        if (removedDog.getColor() == Dog::BLACK) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }
        else if (removedDog.getColor() == Dog::WHITE) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }
        else if (removedDog.getColor() == Dog::BROWN) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }
        else if (removedDog.getColor() == Dog::ORANGE) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }

        counter4[removedDog.getColor()] = removedDog.getId();
        dogsCheck4.push_back(removedDog);
    }
    });

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();

    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();

    std::vector<Dog> allDogs;
    allDogs.insert(allDogs.end(), dogsCheck1.begin(), dogsCheck1.end());
    allDogs.insert(allDogs.end(), dogsCheck2.begin(), dogsCheck2.end());
    allDogs.insert(allDogs.end(), dogsCheck3.begin(), dogsCheck3.end());
    allDogs.insert(allDogs.end(), dogsCheck4.begin(), dogsCheck4.end());
    std::sort(allDogs.begin(), allDogs.end(), dogComparator);

    for(size_t i = 0; i < 4; ++i) {
		for(size_t j = 0; j < count/4; ++j) {
			if(allDogs[i * count/4 + j].getColor() != i && allDogs[i * count/4 + j].getId() == j){
				is_complete = false;
				break;
			}
		}
	}
       
    ASSERT_THAT(is_fifo);
	ASSERT_THAT(is_complete);
	ASSERT_EQUAL(q.empty(), true);
	ASSERT_EQUAL(q.full(), false);
	ASSERT_EQUAL(q.size(), 0);

END_TEST

BEGIN_TEST(PriorityQueueWithOneThread)
    using namespace advcpp;
    constexpr size_t N = 1000;
    WaitableQueue<Dog, std::priority_queue<Dog>> q(N);
    for(size_t i = 0; i < N; ++i) {
        Dog dog(i, Dog::Color::BROWN); 
        q.enqueue(dog);
    }

    ASSERT_EQUAL(q.size(), N);
    
    for(size_t i = 0; i < N; ++i) {
        Dog removedDog(i, Dog::Color::BROWN);
        q.dequeue(removedDog);
        if(removedDog.getId() == i && removedDog.getColor() == Dog::Color::BROWN) {
            ASSERT_PASS();
        }
    }
    ASSERT_EQUAL(q.size(),0);

END_TEST

BEGIN_TEST(PriorityQueueFIFOwithOneConsumerOneProducer)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog, std::priority_queue<Dog>> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;

    std::thread producter([&q]() {
        for(size_t i = 0; i < count; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    std::thread consumer([&q, &is_fifo]() {
        for(size_t i = 0; i < count; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);
            if (removedDog.getId() != i) {
                is_fifo = false;
                break;
            }
        }       
    });
    
    producter.join();
    consumer.join();
    ASSERT_THAT(is_fifo);
    ASSERT_EQUAL(q.size(), 0);

END_TEST


BEGIN_TEST(PriorityQueueFIFOwithTwoProducersOneConsumer)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog, std::priority_queue<Dog>> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;

    std::thread producer1([&q]() {
        for(size_t i = 0; i < count/2; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    std::thread producer2([&q]() {
        for(size_t i = 0; i < count/2; ++i) {
            q.enqueue(Dog(i, Dog::WHITE));
        }   
    });

    size_t blackCounter = 0;
    size_t whiteCounter = 0;

    std::thread consumer([&q, &is_fifo, &blackCounter, &whiteCounter]() {
        for(size_t i = 0; i < count; ++i) {
            
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if(removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() != blackCounter) {
                    is_fifo = false;
                    break;
                }
                ++blackCounter;
            }
            
            if(removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() != whiteCounter) {
                    is_fifo = false;
                    break;
                }
                ++whiteCounter;
            }
        }
    });
    
    producer1.join();
    producer2.join();
    consumer.join();

    ASSERT_THAT(is_fifo);
    ASSERT_EQUAL(q.size(), 0);

END_TEST


BEGIN_TEST(PriorityQueueFIFOwithOneProducerTwoConsumers)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog, std::priority_queue<Dog>> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;

    std::thread producer([&q]() {
        for(size_t i = 0; i < count; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    size_t Counter1 = 0;
    size_t Counter2 = 0;
    std::vector<Dog> dogsCheck1;
    std::vector<Dog> dogsCheck2;

    std::thread consumer1([&q, &is_fifo, &Counter1, &dogsCheck1]() {
        for(size_t i = 0; i < count/2; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if(removedDog.getId() < Counter1) {
                is_fifo = false;
                break;
            }
            Counter1 = removedDog.getId();
            dogsCheck1.push_back(removedDog);
        }
    });
    
    std::thread consumer2([&q, &is_fifo, &Counter2,  &dogsCheck2]() {
        for(size_t i = 0; i < count/2; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if(removedDog.getId() < Counter2) {
                is_fifo = false;
                break;
            }
            Counter2 = removedDog.getId();
            dogsCheck2.push_back(removedDog);
        }
    });

    producer.join();
    consumer1.join();
    consumer2.join();

    dogsCheck1.insert(dogsCheck1.end(), dogsCheck2.begin(), dogsCheck2.end());
    std::sort(dogsCheck1.begin(), dogsCheck1.end(), [](const Dog& a, const Dog& b) {
        return a.getId() < b.getId();
    });
    for(size_t i = 0; i < dogsCheck1.size(); ++i) {
        ASSERT_EQUAL(dogsCheck1[i].getId(), i);
        ASSERT_EQUAL(dogsCheck1[i].getColor(), Dog::BLACK);
    }

    ASSERT_THAT(is_fifo);
    ASSERT_EQUAL(q.size(), 0);

END_TEST


BEGIN_TEST(PriorityQueueFIFOwithFourProducersFourConsumers)
    using namespace advcpp;
    constexpr int N = 1000;
    WaitableQueue<Dog, std::priority_queue<Dog>> q(N);

    constexpr auto count = 1'000'000UL;
    auto is_fifo = true;
    auto is_complete = true;
    
    std::thread producer1([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::BLACK));
        }    
    });

    std::thread producer2([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::WHITE));
        }   
    });

    std::thread producer3([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::BROWN));
        }    
    });

    std::thread producer4([&q]() {
        for(size_t i = 0; i < count/4; ++i) {
            q.enqueue(Dog(i, Dog::ORANGE));
        }   
    });

    size_t counter1[4] = {0};
    size_t counter2[4] = {0};
    size_t counter3[4] = {0};
    size_t counter4[4] = {0};

    std::vector<Dog> dogsCheck1;
    std::vector<Dog> dogsCheck2;
    std::vector<Dog> dogsCheck3;
    std::vector<Dog> dogsCheck4;

    std::thread consumer1([&q, &is_fifo, &counter1, &dogsCheck1]() {
        for(size_t i = 0; i < count/4; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if (removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::BROWN) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::ORANGE) {
                if(removedDog.getId() < counter1[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }

            counter1[removedDog.getColor()] = removedDog.getId();
            dogsCheck1.push_back(removedDog);
        }
    });
    
    std::thread consumer2([&q, &is_fifo, &counter2, &dogsCheck2]() {
        for(size_t i = 0; i < count/4; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if (removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::BROWN) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::ORANGE) {
                if(removedDog.getId() < counter2[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }

            counter2[removedDog.getColor()] = removedDog.getId();
            dogsCheck2.push_back(removedDog);
        }
    });

    std::thread consumer3([&q, &is_fifo, &counter3, &dogsCheck3]() {
        for(size_t i = 0; i < count/4; ++i) {
            Dog removedDog(i, Dog::Color::BROWN);
            q.dequeue(removedDog);

            if (removedDog.getColor() == Dog::BLACK) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::WHITE) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::BROWN) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }
            else if (removedDog.getColor() == Dog::ORANGE) {
                if(removedDog.getId() < counter3[removedDog.getColor()]) {
                    is_fifo = false;
                    break;
                }
            }

            counter3[removedDog.getColor()] = removedDog.getId();
            dogsCheck3.push_back(removedDog);
        }
    });
    
    std::thread consumer4([&q, &is_fifo, &counter4, &dogsCheck4]() {
    for(size_t i = 0; i < count/4; ++i) {
        Dog removedDog(i, Dog::Color::BROWN);
        q.dequeue(removedDog);

        if (removedDog.getColor() == Dog::BLACK) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }
        else if (removedDog.getColor() == Dog::WHITE) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }
        else if (removedDog.getColor() == Dog::BROWN) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }
        else if (removedDog.getColor() == Dog::ORANGE) {
            if(removedDog.getId() < counter4[removedDog.getColor()]) {
                is_fifo = false;
                break;
            }
        }

        counter4[removedDog.getColor()] = removedDog.getId();
        dogsCheck4.push_back(removedDog);
    }
    });

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();

    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();

    std::vector<Dog> allDogs;
    allDogs.insert(allDogs.end(), dogsCheck1.begin(), dogsCheck1.end());
    allDogs.insert(allDogs.end(), dogsCheck2.begin(), dogsCheck2.end());
    allDogs.insert(allDogs.end(), dogsCheck3.begin(), dogsCheck3.end());
    allDogs.insert(allDogs.end(), dogsCheck4.begin(), dogsCheck4.end());
    std::sort(allDogs.begin(), allDogs.end(), dogComparator);

    for(size_t i = 0; i < 4; ++i) {
		for(size_t j = 0; j < count/4; ++j) {
			if(allDogs[i * count/4 + j].getColor() != i && allDogs[i * count/4 + j].getId() == j){
				is_complete = false;
				break;
			}
		}
	}
       
    ASSERT_THAT(is_fifo);
	ASSERT_THAT(is_complete);
	ASSERT_EQUAL(q.empty(), true);
	ASSERT_EQUAL(q.full(), false);
	ASSERT_EQUAL(q.size(), 0);

END_TEST

TEST_SUITE(因果応報 [waitable queue])
    TEST(FIFOwithOneThread)
    TEST(FIFOwithOneConsumerOneProducer)
    TEST(FIFOwithTwoProducersOneConsumer)
    TEST(FIFOwithOneProducerTwoConsumers)
    TEST(FIFOwithFourProducersFourConsumers)

    TEST(PriorityQueueWithOneThread)
    TEST(PriorityQueueFIFOwithOneConsumerOneProducer)
    TEST(PriorityQueueFIFOwithTwoProducersOneConsumer)
    TEST(PriorityQueueFIFOwithOneProducerTwoConsumers)
    TEST(PriorityQueueFIFOwithFourProducersFourConsumers)
END_SUITE
