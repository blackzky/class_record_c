     // FILE * fp;
     // char data[80] = "";
     // int num = 0;
     // char strnum[16]; 
     // long bufsize;
     // char *source = NULL;
     // char *class_to_class, *class_data_to_students;

     // fp = fopen ("classes.dat","r");
     // if (fp!=NULL) {
          // if (fseek(fp, 0L, SEEK_END) == 0) {
               // bufsize = ftell(fp);
               // if (bufsize == -1) { fclose(fp); exit(0); /* Error */ }
               // /* Allocate our buffer to that size. */
               // source = malloc(sizeof(char) * (bufsize + 1));
               // /* Go back to the start of the file. */
               // if (fseek(fp, 0L, SEEK_SET) == 0) { /* Error */ }
               // /* Read the entire file into memory. */
               // size_t newLen = fread(source, sizeof(char), bufsize, fp);
               // if (newLen == 0) {
                    // fputs("Error reading file", stderr);
               // } else {
                    // source[++newLen] = '\0'; /* Just to be safe. */
               // }
          // }
          // //load students from file..
          // //get last id based from the list of all students loaded
          // //set id to last id
          // //...code here..
          // class_to_class = strtok (source, ";");
          // while (class_to_class != NULL) {
               // class_data_to_students =strtok(class_to_class, ":");
               // class_to_class = strtok (NULL, ";");
               // while (class_data_to_students != NULL) {
                    // printf ("%s\n", class_data_to_students);
                    // class_data_to_students = strtok (NULL, ":");
               // }
          // }
          // printf("\nfile: %s", source);
          // getch();
          // free(source); 
     // }
     // fclose(fp);

// //--------------------------------------------
     // //save data to file
     // fp = fopen ("classes.dat","w");
     // if (fp!=NULL) {
          // //print data
          // while(classes->next!=NULL) {
               // classes = classes->next;
               // sprintf(strnum, "%d", classes->data.id);
               // strcat(data, strnum);
               // strcat(data, ",");
               // strcat(data, classes->data.name);
               // strcat(data, ":");
               
               // students = getClass(classes, classes->data.id).students;
               // while(students->next!=NULL){
                    // students = students->next;
                    // sprintf(strnum, "%d", students->data.id);
                    // strcat(data, students->data.firstname);
               // }
               // strcat(data, ";");
          // }
          // printf("%s", data);
          // getch();
     // }
     // fclose(fp);

// */


