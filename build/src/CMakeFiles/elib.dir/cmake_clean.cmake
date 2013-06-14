FILE(REMOVE_RECURSE
  "../libelib.pdb"
  "../libelib.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/elib.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
