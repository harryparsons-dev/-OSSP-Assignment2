//#include <stdio.h>
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// Node *root = NULL;

void *downtime()
{
    int count = 0;
    while (count < 3)
    {
        pthread_mutex_lock(&mutex1);
        balanceTree(root);
        pthread_mutex_unlock(&mutex1);
        sleep(2);
    }
}

void strip(char *s)
{
    char *p2 = s;
    while (*s != '\0')
    {
        if (*s != '\t' && *s != '\n')
        {
            *p2++ = *s++;
        }
        else
        {
            ++s;
        }
    }
    *p2 = '\0';
}

void *ServeClient(char *client)
{

    char *client_no = strdup(client);
    client_no = strtok(client_no, "_");
    char *number = strdup(client_no);

    char *name = strdup(client);

    char *txt = ".txt";
    strcat(name, txt);

    FILE *fp;
    fp = fopen(client, "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {

        char *split;
        split = strtok(line, " ");
        strip(split);
        // printf("Line read - <%s>", split);

        if (strcmp(split, "addNode") == 0)
        {
            pthread_mutex_lock(&mutex1);
            char *num = strtok(NULL, split);
            int num_int = atoi(num);
            root = addNode(root, num_int);
            pthread_mutex_unlock(&mutex1);
            printf("%sinsertNode %d\n", number, num_int);
        }
        else if (strcmp(split, "removeNode") == 0)
        {
            pthread_mutex_lock(&mutex1);
            char *num = strtok(NULL, split);
            int num_int = atoi(num);
            root = removeNode(root, num_int);
            pthread_mutex_unlock(&mutex1);
            printf("%sdeleteNode %d\n", number, num_int);
        }
        else if (strcmp(split, "countNodes") == 0)
        {
            pthread_mutex_lock(&mutex1);
            int count = countNodes(root);
            printf("%scountNodes = %d\n", number, count);
            pthread_mutex_unlock(&mutex1);
        }
        else if (strcmp(split, "avgSubtree") == 0)
        {
            pthread_mutex_lock(&mutex1);
            float avg = avgSubtree(root);
            printf("%savgSubtree = %f\n", number, avg);
            pthread_mutex_unlock(&mutex1);
        }
    }

    fclose(fp);
    if (line)
    {
        free(line);
    }

    // exit(EXIT_SUCCESS);

    displaySubtree(root);
}
