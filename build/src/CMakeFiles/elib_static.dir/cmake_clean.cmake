FILE(REMOVE_RECURSE
  "../libelib_static.pdb"
  "../libelib_static.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/elib_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
