/* The build system does not like "header-only" libraries
 * So this is a dummy file to trick it into thinking it is not headerless
 * 
 * More specificly,  if only this library is built, the build will still
 * try and create the shared and static libraries. but it needs at least
 * one source file to do so. 
 */
