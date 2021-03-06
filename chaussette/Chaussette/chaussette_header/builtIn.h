#ifndef BUILTIN_H
# define BUILTIN_H_

# define NB_BUILT (8)

//setter
void setBuiltIn(t_ptr *built_in);
//function
int asciiChaussetteAt(char **split, char **words);
int writeChaussetteAt(char **split, char **words);
int asciiChaussette(char **split, char **words);
int writeChaussette(char **split, char **words);
int returning(char **split, char **words);
int readFrom(char **split, char **words);
int setString(char **split, char **words);
int dumpChaussette(char **split, char **words);

#endif