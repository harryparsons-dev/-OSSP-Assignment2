
void *downtime() {

}

void *ServeClient(char *client) {
  
    char* name = strdup(client);
    char * txt= ".txt";
    strcat(name,txt);
    printf("%s", name);
    FILE *fp;
    fp = fopen(client,"r");

    if(fp == NULL){
        printf("Error: failed to open file");
    }
    
   // char* ch = malloc(sizeof(char) * 255);
    char ch;
    while(ch != EOF){
        printf("%c ",ch);
        ch = getc(fp);
    }






    fclose(fp);





    // char* command = malloc(sizeof(char) * strlen (client));




    // char* command = strdup(client);
    // printf("%s", command);
  
    // char* token = strtok(command," ");

    //  printf("%s ", token);
    //  if(command == "addNode"){
        
    //  }
     free(name);

 }
