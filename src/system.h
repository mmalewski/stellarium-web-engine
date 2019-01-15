/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd
 *
 * This program is licensed under the terms of the GNU AGPL v3, or
 * alternatively under a commercial licence.
 *
 * The terms of the AGPL v3 license can be found in the main directory of this
 * repository.
 */

/*
 * File: system.h
 * Contains some functions whose implementation depend on the target OK
 */

/*
 * Function: sys_log
 * Print a line of text to the console.
 *
 * It's better to call one of the LOG macro instead.
 */
void sys_log(const char *msg);

/*
 * Function: sys_get_unix_time
 * Return the unix time (in seconds)
 */
double sys_get_unix_time(void);

/*
 * Function: sys_get_utc_offset
 * Return the local time UTC offset in seconds
 */
int sys_get_utc_offset(void);

/*
 * Function: sys_get_user_dir
 * Return the user data directory.
 */
const char *sys_get_user_dir(void);

/*
 * Function: sys_make_dir
 * Create all the directories parent of a given file path if they do not
 * exist yet.
 *
 * For example, sys_make_dir("/a/b/c.txt") will create /a/ and /a/b/.
 *
 * Return:
 *   0 in case of success, otherwise an error code.
 */
int sys_make_dir(const char *path);

/*
 * Function: sys_device_sensors
 * Get the readings from the device accelerometers and magnetometer.
 *
 * Parameters:
 *   enable - set to 1 to enable the sensors, 0 to stop them.
 *   acc    - get the accelerometer readings.
 *   mag    - get the magnetomer readings.
 *
 * Return:
 *   0 on success.
 */
int sys_device_sensors(int enable, double acc[3], double mag[3]);

int sys_get_position(double *lat, double *lon, double *alt, double *accuracy);

/*
 * Function: sys_translate
 * Translate a string in current locale.
 *
 * Parameters:
 *   domain - optional domain hint for the translator.
 *   str    - the string to translate.
 *
 * Return:
 *   The translated string.
 */
const char *sys_translate(const char *domain, const char *str);

/*
 * Function: sys_list_dir
 * List all the files and directories in a local directory.
 *
 * Parameters:
 *   dir    - A local dir.
 *   user   - User data passed to the callback.
 *   f      - A callback function called once per file/dir.
 */
int sys_list_dir(const char *dir, void *user,
                 int (*f)(void *user, const char *path, int is_dir));

/*
 * Function: sys_list_fonts
 * List all the font files available.
 *
 * Parameters:
 *   user   - User data passed to the callback.
 *   f      - Callback function called once per font file.  If it returns
 *            a value different than zero we stop the iteration.  The
 *            callback takes the following arguments:
 *              user        - The original user data.
 *              path        - Path to the font file.
 *              name        - Name for the font.
 *              fallback    - If not NULL, name of a previous font this font
 *                            should be used as a fallback for.
 *              scale       - Auto scale to apply (this is to fix a problem
 *                            with nanovg that seems to render some fonts
 *                            with the wrong size!).
 * Return:
 *   The number of fonts listed.
 */
int sys_list_fonts(void *user,
                   int (*f)(void *user, const char *path,
                            const char *name, const char *fallback,
                            float scale));

/*
 * Global structure that holds pointers to functions that allow to change
 * the behavior of system calls.
 */
typedef struct {
    void *user;
    void (*log)(void *user, const char *msg);
    const char *(*get_user_dir)(void *user);
    int (*device_sensors)(void *user, int enable,
                          double acc[3], double mag[3]);
    int (*get_position)(void *user, double *lat, double *lon,
                        double *alt, double *accuracy);
    const char *(*translate)(void *user, const char *domain, const char *str);
    int (*list_dir)(void *user, const char *dir, void *cuser,
                    int (*f)(void *user, const char *path, int is_dir));
    int (*list_fonts)(void *user, void *cuser,
                      int (*f)(void *user, const char *path, const char *name,
                               const char *fallback, float scale));
} sys_callbacks_t;

extern sys_callbacks_t sys_callbacks;
