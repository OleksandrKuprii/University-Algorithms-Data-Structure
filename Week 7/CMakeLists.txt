cmake_minimum_required(VERSION 3.16)
project(counters_pogil C)

add_executable(words_counting WordCounter/main_words.c WordCounter/Counter.h WordCounter/Counter.c)
add_executable(letters_counting LetterCounter/main_letters.c LetterCounter/LetterCounter.c LetterCounter/LetterCounter.h LetterCounter/LangugageRecognizer.c LetterCounter/LangugageRecognizer.h)

foreach(exec words_counting letters_counting)
    message("Setting properties of ${exec}")
    set_target_properties(${exec}
            PROPERTIES
            LANGUAGE C
            C_STANDARD 11
            C_STANDARD_REQUIRED YES
            C_EXTENSIONS NO
            )
endforeach()

list(APPEND COMPILE_FLAGS -Og -Wall -Wextra -pedantic -Werror)

target_compile_options(words_counting PRIVATE ${COMPILE_FLAGS})
target_compile_options(letters_counting PRIVATE ${COMPILE_FLAGS})

list(APPEND files alice0.txt alice1.txt alice2.txt alice3.txt)

foreach(file IN LISTS files)
    configure_file(${file} ${file} COPYONLY)
endforeach()

# enable ASAN - linux and mac only! disable this one if not available on your system
# message("If you get an error compiling on your system, remove the line below.")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")