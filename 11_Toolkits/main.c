#include <glib.h>
#include <stdio.h>


int compare_point(gconstpointer a, gconstpointer b) {
    return b - a;
}


int main() {
    GHashTable *hash = g_hash_table_new(g_str_hash, g_int_equal);
    char buf[81] = {0};
    while (fgets(buf, 81, stdin) != NULL) {
        gchar **words = g_strsplit_set(buf, " \t\n", 80);
        for (char **i = words; *i; i++) {
            gpointer gp = g_hash_table_lookup(hash, *i);
            if (gp != NULL) {
                int n = GPOINTER_TO_INT(gp) + 1;
                g_hash_table_insert(hash, g_strdup(*i), GINT_TO_POINTER(n));
            } else {
                g_hash_table_insert(hash, g_strdup(*i), GINT_TO_POINTER(1));
            }
        }
    }
    GList *lst = g_hash_table_get_values(hash), *it;
    lst = g_list_sort(lst, (GCompareDataFunc) compare_point);
    for (it = lst; it; it = it->next) {
        printf("%d\n", GPOINTER_TO_INT(it->data));
    }
    g_hash_table_destroy(hash);
    g_list_free(lst);
    return 0;
}