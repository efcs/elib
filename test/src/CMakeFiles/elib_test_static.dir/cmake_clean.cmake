FILE(REMOVE_RECURSE
  "../../bin/elib_test_static.pdb"
  "../../bin/elib_test_static"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/elib_test_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
