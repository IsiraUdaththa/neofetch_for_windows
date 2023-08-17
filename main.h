/* Forward-declare our functions so users can mention them in their
 * configs at the top of the file rather than near the bottom. */

static char *get_title(),
        *get_bar(),
        *get_name(),
        *get_manufacturer(),
        *get_model(),

        *get_cpu(),
        *get_gpu1(),
        *get_gpu2(),
        *get_memory(),

        *get_os(),
        *get_battery_percentage(),
        *get_packages_pacman(),
        *get_shell(),
        *get_resolution(),
        *get_terminal(),

        *get_disk_usage_root(),
        *get_disk_usage_home(),

        *get_colors1(),
        *get_colors2(),
        *spacer();

#define REMOVE(A) { (A), NULL, sizeof(A) - 1 , 0 }
#define REPLACE(A, B) { (A), (B), sizeof(A) - 1, sizeof(B) - 1 }
#define SPACER {" ", spacer, true},