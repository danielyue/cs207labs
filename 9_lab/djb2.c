// taken from http://www.cse.yorku.ca/~oz/hash.html

unsigned long
djb2hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
