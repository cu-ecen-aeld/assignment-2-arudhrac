#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    // Opening syslog utility
    openlog("Running write.c", LOG_PID, LOG_USER);

    if (argc != 3)
    {
        errno = EINVAL;
        perror("ERROR:Required 2 arguements!");
        syslog(LOG_ERR, "ERROR:Entered %d arguements. Required 2.", argc - 1);
        printf("ERROR:Entered %d arguements. Required 2.\n", argc - 1);
        printf("Usage: <directory_path> <string>\n");
        return 1;
    }

    // Opening FILE
    char *dir = argv[1];
    int fd = open(dir, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("ERROR: Open Error!");
        syslog(LOG_ERR, "ERROR:Failed to open file %s", dir);
        return 1;
    }
    syslog(LOG_DEBUG, "Opened %s SUCCESSFULLY !", dir);

    // Writing String to FILE
    char *str = argv[2];
    ssize_t nr = write(fd, str, strlen(str));
    if (nr == -1)
    {
        perror("ERROR: Write Error !");
        syslog(LOG_ERR, "ERROR: Writing \" %s \" to file %s FAILED", str, dir);
        close(fd);
        return 1;
    }
    syslog(LOG_DEBUG, "Writing \" %s \" to file %s SUCCESSFULLY !", str, dir);
    syslog(LOG_DEBUG, "SUCCESS: Data Written: %ld\n", nr);

    // Reading Srting from FILE
    lseek(fd, 0, SEEK_SET);

    char buffer[100];
    ssize_t cr = read(fd, buffer, sizeof(buffer) - 1);
    if (cr == -1)
    {
        perror("ERROR:Read Error");
        syslog(LOG_ERR, "ERROR:Reading from file %s FAILED", dir);
        close(fd);
        return 1;
    }
    buffer[cr] = '\0';
    syslog(LOG_DEBUG, "SUCCESS: Data Read: %ld\n", cr);
    printf("Data: \n%s\n", buffer);

    close(fd);

    return 0;
}