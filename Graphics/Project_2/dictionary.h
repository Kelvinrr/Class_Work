/**
 * Simple Dictionary implementation in C
 *
 *
 *
 */

#define HASHSIZE 64

typedef struct nlist {
  struct nlist *next;
  char *name;
  double *val;
} linked_list;

typedef linked_list *Dict;

unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

double lookup(Dict dict, char *s) {
  linked_list *np;
  for (np = &dict[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np->val;
  return NULL;
}

// char* strdup(char* s) {
//     char* p;
//     p = (char *) malloc(strlen(s)+1);
//     if (p != NULL)
//        strcpy(p, s);
//     return p;
// }

linked_list *install(Dict dict, char *name, double obj) {
  linked_list *np;
  unsigned hashval;
  if ((np = lookup(dict, name)) == NULL) { /* not found */
    np = (linked_list *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = &dict[hashval];
    dict[hashval] = *np;
  } else                   /* already there */
    free((void *)np->val); /*free previous defn */
  if ((np->val = obj)) == NULL)
    return NULL;
  return np;
}
