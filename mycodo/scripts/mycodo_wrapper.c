#include <linux/limits.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	setuid(0);
	char cmd[255];

	if (argc > 1) {
		if (strcmp(argv[1], "backup-create") == 0) {

		    char path[255];
            strncpy(path, argv[0], sizeof(path));
            dirname(path);

			char restoreScript[255];
			strncpy(restoreScript, "/bin/bash ", sizeof(restoreScript));
			strncat(restoreScript, path, sizeof(restoreScript));
			strncat(restoreScript, "/upgrade_commands.sh backup-create", sizeof(restoreScript));
			system(restoreScript);

        } else if (strcmp(argv[1], "backup-delete") == 0 && (argc > 2)) {

			sprintf(cmd, "rm -rf /var/Mycodo-backups/Mycodo-backup-%s", argv[2]);
			system(cmd);

		} else if (strcmp(argv[1], "backup-restore") == 0 && (argc > 2)) {

		    char path[255];
            strncpy(path, argv[0], sizeof(path));
            dirname(path);

			char restoreScript[255];
			strncpy(restoreScript, "/bin/bash ", sizeof(restoreScript));
			strncat(restoreScript, path, sizeof(restoreScript));
			sprintf(cmd, "/upgrade_commands.sh backup-restore %s", argv[2]);
			strncat(restoreScript, cmd, sizeof(restoreScript));
			system(restoreScript);

        } else if (strcmp(argv[1], "mycodo_restart_debug") == 0) {

			sprintf(cmd, "service mycodo stop");
			system(cmd);
			sprintf(cmd, "/../../env/bin/Python /../mycodo_daemon.py -d");
			system(cmd);
			
		} else if (strcmp(argv[1], "restart") == 0) {

			sprintf(cmd, "sleep 10 && shutdown now -r");
			system(cmd);

		} else if (strcmp(argv[1], "mycodo_restart") == 0) {

			sprintf(cmd, "service mycodo restart");
			system(cmd);
			
			} else if (strcmp(argv[1], "shutdown") == 0) {

			sprintf(cmd, "sleep 10 && shutdown now -h");
			system(cmd);

		} else if (strcmp(argv[1], "mycodo_start") == 0) {

			sprintf(cmd, "service mycodo start");
			system(cmd);

		} else if (strcmp(argv[1], "mycodo_stop") == 0) {

			sprintf(cmd, "service mycodo stop");
			system(cmd);

		} else if (strcmp(argv[1], "upgrade") == 0) {

            char path[255];
            strncpy(path, argv[0], sizeof(path));
            dirname(path);

			char updateScript[255];
			strncpy(updateScript, "/bin/bash ", sizeof(updateScript));
			strncat(updateScript, path, sizeof(updateScript));
			strncat(updateScript, "/upgrade_commands.sh upgrade", sizeof(updateScript));
			system(updateScript);

		}
	} else {

		printf("mycodo-wrapper: A wrapper to allow the mycodo web interface\n");
		printf("                to stop and start the daemon and update the\n");
		printf("                mycodo system to the latest version.\n\n");
		printf("Usage: mycodo-wrapper start|restart|debug|update|restore [commit]\n\n");
		printf("Options:\n");
        printf("   backup-create:              Create Mycodo backup\n");
		printf("   backup-delete [DIRECTORY]:  Delete Mycodo backup [DIRECTORY]\n");
		printf("   backup-restore [DIRECTORY]: Restore Mycodo from backup [DIRECTORY]\n");
		printf("   mycodo_restart:             Restart the mycodo daemon in normal mode\n");
		printf("   mycodo_restart_debug:       Restart the mycodo daemon in debug mode\n");
		printf("   mycodo_start:               Start the mycodo daemon\n");
		printf("   mycodo_stop:                Stop the mycodo daemon\n");
		printf("   restart:                    Restart the computer after a 10 second pause\n");
		printf("   shutdown:                   Shutdown the computer after a 10 second pause\n");
		printf("   upgrade:                    Upgrade Mycodo to the latest version on github\n");
	}

	return 0;
}
