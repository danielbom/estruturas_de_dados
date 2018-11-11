#ifndef MORE_FILES
#define MORE_FILES

// Conta a quantidade de linhas do arquivo
int flines(FILE* file)
{
    int count = 0;
    rewind(file);
    
    while(!feof(file))
        count += fgetc(file) == '\n';

    rewind(file);
    return count;
}
// Conta a ocorrencia de um determinado caracter arquivo
int fcount(FILE* file, char what, char util)
{
    char c = fgetc(file);   // character of my file
    int count = c == what;  // Count the occurence of 'what'
    int iter = 1;           // Count of fgets executed
    while(c != EOF && c != util)
    {
        c = fgetc(file);
        count += c == what;
        iter++;
    }
    fseek(file, -iter, SEEK_CUR);
    return count;
}

#endif