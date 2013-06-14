FILE(REMOVE_RECURSE
  "../elib_test_static.pdb"
  "../elib_test_static"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/elib_test_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
