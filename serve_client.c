pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;



void *downtime()
{

  sleep(2);  
   pthread_mutex_lock(&mutex1);  
    //root = balanceTree(root);  
    pthread_mutex_unlock(&mutex1);
    sleep(2);  
    pthread_mutex_lock(&mutex1);
    //root = balanceTree(root);  
    pthread_mutex_unlock(&mutex1);
    sleep(2);  
    pthread_mutex_lock(&mutex1);  
   // root = balanceTree(root); 
    pthread_mutex_unlock(&mutex1);

    return NULL;
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

    char *client_no = NULL;
    client_no =  strdup(client);
    char *saveptr = NULL;
    client_no = strtok_r(client_no, "_",&saveptr);
    char *number = strdup(client_no);

    char *name = strdup(client);

    char *txt = ".txt";
    strcat(name, txt);

    FILE *fp;
    fp = fopen(client, "r");

    if (fp == NULL)
        return 0;

    char line[128];
  
    while(fgets(line,128,fp) != NULL){
    
        char *split;
        split = strtok_r(line, " ",&saveptr);
        strip(split);


        if (strcmp(split, "addNode") == 0)
        {
            
            pthread_mutex_lock(&mutex1);      
            char *num = strtok_r(NULL, split,&saveptr);
            unsigned int num_int = atoi(num);
            root = addNode(root, num_int);
            printf("%sinsertNode %u\n", number, num_int);
            pthread_mutex_unlock(&mutex1);
        }
        else if (strcmp(split, "removeNode") == 0)
        {
            pthread_mutex_lock(&mutex1);
            char *num = strtok_r(NULL, split,&saveptr);
            unsigned int num_int = atoi(num);
            root = removeNode(root, num_int);
            printf("%sdeleteNode %u\n", number, num_int);  
            pthread_mutex_unlock(&mutex1);
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

    free(client_no); 

    free(name);

    free(number);

     return NULL;
    
}
