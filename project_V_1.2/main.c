#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_ACCOUNTS        100

typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char account_no[12];
    char name[100];
    char mail[100];
    double balance;
    char mobile[15];
    date d_open;
} user;

user accounts[MAX_ACCOUNTS];        //accounts data
int count = 0;                      //accounts number

void loadAccounts()
{
    const char* filename="accounts.txt";
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return 0;
    }


    char line[400];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* token;
        token = strtok(line, ",");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }
        strcpy(accounts[count].account_no,token);

        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }
        strcpy(accounts[count].name, token);

        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }
        strcpy(accounts[count].mail, token);

        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }
        accounts[count].balance = atof(token);

        token = strtok(NULL, ",");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }
        strcpy(accounts[count].mobile, token);

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }

        accounts[count].d_open.month=atoi(token);
        token = strtok(NULL, " ");
        if (token == NULL)
        {
            printf("Invalid file format: %s\n", filename);
            break;
        }
        accounts[count].d_open.year = atoi(token);
        count++;
        if (count >= MAX_ACCOUNTS)
        {
            printf("Maximum account limit reached: %d\n", MAX_ACCOUNTS);
            break;
        }
    }

    fclose(file);
}

int login()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    FILE* file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file: users.txt\n");
        return 0;
    }

    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2];  // +2 for space and null

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char storedUsername[MAX_USERNAME_LENGTH];
        char storedPassword[MAX_PASSWORD_LENGTH];

        sscanf(line, "%s %s", storedUsername, storedPassword);

        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0)
        {
            fclose(file);
            system("cls");
            printf("welcome to the system ,%s\n",storedUsername);
            loadAccounts();
            return count;  // Successful login
        }
    }

    fclose(file);
    return 0;
}
void save(){
    const char* filename="accounts.txt";
    int i ;
    FILE* file = fopen(filename, "w+");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    for(i=0;i<count;i++){

        fprintf(file,"%s,%s,%s,%0.2f,%s,%d-%d \n",accounts[i].account_no,accounts[i].name,accounts[i].mail,accounts[i].balance,accounts[i].mobile,accounts[i].d_open.month,accounts[i].d_open.year);

    }
    printf("\nsaved succesfully\n");
    fclose(file);
}
void quit(){
    printf("Are you sure thet you want to exit?\n1)yes                  2)no\n");
    int val;
    scanf("%d",&val);
    if(val==1)
        exit(1);
}

int main()
{
    printf("number of the accounts:%d", login());
    save();
    quit();

    return 0;
}
