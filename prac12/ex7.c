#include <stdio.h>
#include <stdlib.h>
#define NAME_MAX_LEN 31
#define BANK_FILENAME "bankaccounts.dat"

typedef struct bank_account
{
    char first_name[NAME_MAX_LEN + 1];
    char last_name[NAME_MAX_LEN + 1];
    int account_number;
    double balance;
} bank_account;

/* Read an account number from standard input, displaying the provided
 * message. Repeat until a number is read in.
 */
int read_account_number(const char *message)
{
    int account_number;
    for (;;)
    {
        printf("%s", message);
        if (scanf("%d", &account_number) < 1)
        {
            printf("Invalid account number\n");
        }
        else
        {
            break;
        }
    }
    return account_number;
}

/* Read a name from standard input, displaying the provided message.
 * Repeat until a string is read in.
 */
void read_name(const char *message, char *name)
{
    for (;;)
    {
        printf("%s", message);
        if (scanf("%31s", name) < 1)
        {
            printf("Invalid name\n");
        }
        else
        {
            break;
        }
    }
}

/* Read an monetary value from standard input, displaying the provided
 * message. Repeat until a number is read in.
 */
double read_transfer_amount(const char *message)
{
    double amount;
    for (;;)
    {
        printf("%s", message);
        if (scanf("%lf", &amount) < 1 || amount < 0.0)
        {
            printf("Invalid amount to transfer\n");
        }
        else
        {
            break;
        }
    }
    return amount;
}

/* Return the index of an account with the provided account number.
 * Returns -1 if no accounts with that number exit
 */
int find_account(int account_number)
{
    FILE *fp = fopen(BANK_FILENAME, "r");
    int account_index = -1;
    if (fp)
    {
        bank_account account;
        int current_index = 0;
        while (fread(&account, sizeof(account), 1, fp) == 1)
        {
            if (account.account_number == account_number)
            {
                account_index = current_index;
                break;
            }
            current_index++;
        }
        fclose(fp);
    }
    return account_index;
}

/* Appends the provided account to the end of the accounts file
 */
void append_account(bank_account account)
{
    FILE *fp = fopen(BANK_FILENAME, "a");
    if (!fp)
    {
        perror(BANK_FILENAME);
        exit(1);
    }
    fwrite(&account, sizeof(account), 1, fp);
    fclose(fp);
}

/* Returns the number of accounts in the file
 */
int get_total_accounts(void)
{
    FILE *fp = fopen(BANK_FILENAME, "r");
    if (!fp)
    {
        // File does not exist
        return 0;
    }
    // Jump to end of file
    fseek(fp, 0, SEEK_END);
    fclose(fp);
    // Calculate number of records
    long file_size_bytes = ftell(fp);
    return file_size_bytes / sizeof(bank_account);
}

/* Read the account with the given index from the bank accounts file
 */
bank_account read_account(int account_index)
{
    FILE *fp = fopen(BANK_FILENAME, "r");
    if (!fp)
    {
        perror(BANK_FILENAME);
        exit(1);
    }
    fseek(fp, account_index * sizeof(bank_account), SEEK_SET);
    bank_account account;
    fread(&account, sizeof(account), 1, fp);
    fclose(fp);
    return account;
}

/* Write the account into the bank accounts file with the given index
 */
void write_account(int account_index, bank_account account)
{
    FILE *fp = fopen(BANK_FILENAME, "r+");
    if (!fp)
    {
        perror(BANK_FILENAME);
        exit(1);
    }
    fseek(fp, account_index * sizeof(bank_account), SEEK_SET);
    fwrite(&account, sizeof(account), 1, fp);
    fclose(fp);
}

void display_accounts(void)
{
    FILE *fp = fopen(BANK_FILENAME, "r");
    if (fp)
    {
        bank_account account;
        while (fread(&account, sizeof(account), 1, fp) == 1)
        {
            printf("%10d%31s %-31s$%.2f\n", account.account_number,
                   account.first_name,
                   account.last_name,
                   account.balance);
        }
        fclose(fp);
    }
}

void create_account(void)
{
    printf("Create account\n");
    bank_account new_account;
    new_account.account_number = read_account_number("Enter account number: ");
    int account_index = find_account(new_account.account_number);
    if (account_index == -1)
    {
        read_name("Enter first name: ", new_account.first_name);
        read_name("Enter last name: ", new_account.last_name);
        new_account.balance = 0.0;
        append_account(new_account);
    }
    else
    {
        printf("Account already exists\n");
    }
}

void delete_account(void)
{
    printf("Delete account\n");
    int account_number = read_account_number("Enter account number: ");
    int account_index = find_account(account_number);
    if (account_index != -1)
    {
        // We will simply read all the accounts in, then write them all
        // out, save for the deleted one
        FILE *fp = fopen(BANK_FILENAME, "r");
        if (!fp)
        {
            // This should not happen as find_account succeeded
            perror(BANK_FILENAME);
            exit(1);
        }
        // Jump to end of file
        fseek(fp, 0, SEEK_END);
        // Calculate number of records
        int num_accounts = ftell(fp) / sizeof(bank_account);
        // Jump back to beginning
        fseek(fp, 0, SEEK_SET);
        // Read all the accounts into memory
        bank_account *accounts = malloc(sizeof(bank_account) * num_accounts);
        fread(accounts, sizeof(bank_account), num_accounts, fp);
        // Close the file
        fclose(fp);
        // Reopen for writing
        fp = fopen(BANK_FILENAME, "w");
        if (!fp)
        {
            perror(BANK_FILENAME);
            exit(1);
        }
        // Write the first 'account_index' accounts
        fwrite(accounts, sizeof(bank_account), account_index, fp);
        // Now, skip over one and write out the rest
        fwrite(&accounts[account_index + 1], sizeof(bank_account), num_accounts - account_index - 1, fp);
        // Close the file
        fclose(fp);
    }
    else
    {
        printf("Account does not exist\n");
    }
}

void deposit_funds(void)
{
    printf("Deposit funds\n");
    int account_number = read_account_number("Enter account number: ");
    int account_index = find_account(account_number);
    if (account_index != -1)
    {
        bank_account account = read_account(account_index);
        double amount = read_transfer_amount("Enter amount of money to deposit:$");
        account.balance += amount;
        write_account(account_index, account);
    }
    else
    {
        printf("Account does not exist\n");
    }
}

void withdraw_funds(void)
{
    printf("Withdraw funds\n");
    int account_number = read_account_number("Enter account number: ");
    int account_index = find_account(account_number);
    if (account_index != -1)
    {
        bank_account account = read_account(account_index);
        double amount = read_transfer_amount("Enter amount of money to withdraw: $");
        if (account.balance >= amount)
        {
            account.balance -= amount;
            write_account(account_index, account);
        }
        else
        {
            printf("Account has insufficient funds\n");
        }
    }
    else
    {
        printf("Account does not exist\n");
    }
}

int main(void)
{
    int selection;
    while (selection != 6)
    {
        printf("\n1. Create new account\n");
        printf("2. Delete account\n");
        printf("3. Display accounts\n");
        printf("4. Deposit funds\n");
        printf("5. Withdraw funds\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        if (scanf("%d", &selection) < 1)
        {
            printf("Invalid input.\n");
            continue;
        }
        switch (selection)
        {
        case 1:
            create_account();
            break;
        case 2:
            delete_account();
            break;
        case 3:
            display_accounts();
            break;
        case 4:
            deposit_funds();
            break;
        case 5:
            withdraw_funds();
            break;
        case 6:
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}