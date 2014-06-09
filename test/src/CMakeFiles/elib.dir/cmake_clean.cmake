FILE(REMOVE_RECURSE
  "../../bin/libelib.pdb"
  "../../bin/libelib.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/elib.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
