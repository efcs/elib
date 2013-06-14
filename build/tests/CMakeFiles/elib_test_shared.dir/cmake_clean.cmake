FILE(REMOVE_RECURSE
  "../elib_test_shared.pdb"
  "../elib_test_shared"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/elib_test_shared.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
