if(EXISTS "D:/govnocods/build_new/RelWithDebInfo/lesson_test.exe")
  if(NOT EXISTS "D:/govnocods/build_new/lesson_test_74785a0e_RelWithDebInfo_tests.cmake" OR
     NOT "D:/govnocods/build_new/lesson_test_74785a0e_RelWithDebInfo_tests.cmake" IS_NEWER_THAN "D:/govnocods/build_new/RelWithDebInfo/lesson_test.exe" OR
     NOT "D:/govnocods/build_new/lesson_test_74785a0e_RelWithDebInfo_tests.cmake" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
    include("D:/govnocods/build_new/lesson_test_74785a0e_RelWithDebInfo_discovery.cmake")
  endif()
endif()
if(EXISTS "D:/govnocods/build_new/lesson_test_74785a0e_RelWithDebInfo_tests.cmake")
  include("D:/govnocods/build_new/lesson_test_74785a0e_RelWithDebInfo_tests.cmake")
else()
  add_test(lesson_test_NOT_BUILT lesson_test_NOT_BUILT)
endif()
