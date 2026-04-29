#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameCafe.h"

struct slotCustomerData slots[1000];
int slotCount = 0;
int adminCount = 0;
char loggedUserName[50];

int checkUserPass()
{
    FILE *fp;
    fp = fopen("adminUserPass.txt", "r+");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return 0;
    }
    struct AdminUserData adminUserData[40];
    while(fscanf(fp, " %[^,], %s", adminUserData[adminCount].username, adminUserData[adminCount].pass) == 2)
    {
        adminCount++;
    }
    char username[50];
    char pass[50];
    printf("Enter Admin Username: ");
    scanf(" %s", username);
    strcpy(loggedUserName, username);
    printf("Enter Password: ");
    scanf(" %s", pass);
    for(int i = 0; i < adminCount; i++)
    {
        if((strcmp(username, adminUserData[i].username) == 0) && (strcmp(pass, adminUserData[i].pass) == 0))
        {
            printf("Login Successful. Welcome Admin (Username: %s).\n\n", username);
            fclose(fp);
            return 1;
        }
    }
    printf("Invalid Credentials. Login Unsuccessful for Username: %s).\n\n", username);
    fclose(fp);
    return 0;
}

void changeAdminPassword()
{
    FILE *fp;
    fp = fopen("adminUserPass.txt", "r+");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return;
    }
    int adminCount = 0;
    struct AdminUserData adminUserData[40];
    while(fscanf(fp, " %[^,], %s", adminUserData[adminCount].username, adminUserData[adminCount].pass) == 2)
    {
        adminCount++;
    }
    char enteredCurrentPass[50];
    char newPasswordToSet_1[50];
    char newPasswordToSet_2[50];
    for(int i = 0; i < adminCount; i++)
    {
        if(strcmp(loggedUserName, adminUserData[i].username) == 0)
        {
            printf("Enter the Current Password: ");
            scanf(" %s", enteredCurrentPass);
            printf("Enter the New Password: ");
            scanf(" %s", newPasswordToSet_1);
            printf("Confirm the New Password: ");
            scanf(" %s", newPasswordToSet_2);
            if(strcmp(enteredCurrentPass, adminUserData[i].pass) == 0)
            {
                if(strcmp(newPasswordToSet_1, newPasswordToSet_2) == 0)
                {
                    fclose(fp);
                    fp = fopen("adminUserPass.txt", "w+");
                    if(fp == NULL)
                    {
                        printf("File Does Not Exist.\n");
                        return;
                    }
                    fprintf(fp, "");
                    fclose(fp);
                    fp = fopen("adminUserPass.txt", "w+");
                    if(fp == NULL)
                    {
                        printf("File Does Not Exist.\n");
                        return;
                    }
                    strcpy(adminUserData[i].pass, newPasswordToSet_1);
                    fprintf(fp, "%s, %s\n", adminUserData[i].username, adminUserData[i].pass);
                    printf("Password Change Successful.\n\n");
                }
                else
                {
                    printf("New Password doesn't Match with the Confirmed Password.\n\n");
                }
            }
            else
            {
                printf("Password Change Unsuccessful. You Have the Entered the Wrong Current Password.\n\n");
            }
            fclose(fp);
        }
    }
}

void registerAnotherAdmin()
{
    FILE *fp;
    fp = fopen("adminUserPass.txt", "r+");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return;
    }
    int adminCount = 0;
    struct AdminUserData adminUserData[40];
    while(fscanf(fp, " %[^,], %s", adminUserData[adminCount].username, adminUserData[adminCount].pass) == 2)
    {
           adminCount++;
    }
    char newUserName[50];
    char newUserPassword[50];
    printf("Enter the New Admin Username (Without Space or Comma): ");
    scanf(" %s", newUserName);
    printf("Enter the Password for %s: ", newUserName);
    scanf(" %s", newUserPassword);
    adminCount++;
    strcpy(adminUserData[adminCount].username, newUserName);
    strcpy(adminUserData[adminCount].pass, newUserPassword);
    fclose(fp);
    fp = fopen("adminUserPass.txt", "a");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return;
    }
    fprintf(fp, "%s, %s\n", adminUserData[adminCount].username, adminUserData[adminCount].pass);
    fclose(fp);
    printf("Successfully Added the New Admin User.\n\n");
}

void loadSlotDataFromFile(){
    FILE *fp;
    slotCount = 0;
    fp = fopen("slotData.txt", "r+");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return;
    }
    while(fscanf(fp, " %[^,], %d, %d, %d, %d", slots[slotCount].customerName, &slots[slotCount].deviceSlotIndex, &slots[slotCount].timeSlotStart, &slots[slotCount].timeSlotEnd, &slots[slotCount].withVRHeadset) == 5)
    {
        slotCount++;
    }
    fclose(fp);
}

struct slotCustomerData inputSlotData()
{
    struct slotCustomerData data;
    printf("Enter Customer's Name: ");
    getchar();
    fgets(data.customerName, sizeof(data.customerName), stdin);
    data.customerName[strcspn(data.customerName, "\n")] = '\0';
    printf("Enter the Device Index to Book (1 - 8): ");
    scanf("%d", &data.deviceSlotIndex);
    printf("Enter the Time to Start the Session (Only the Hours in 24 Hrs Format): ");
    scanf("%d", &data.timeSlotStart);
    printf("Enter the Time to End the Session (Only the Hours in 24 Hrs Format): ");
    scanf("%d", &data.timeSlotEnd);
    printf("Enter 1 if You Want to Use VR, else Enter 0: ");
    scanf("%d", &data.withVRHeadset);
    printf("\n");
    return data;
}

void saveSlotData(struct slotCustomerData data)
{
    FILE *fp;
    fp = fopen("slotData.txt", "a");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return;
    }
    if (checkIfSlotIsBooked(data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd) == 1)
    {
        printf("The Device Slot is Already Booked.\n\n");
    }
    else if(!(data.deviceSlotIndex >= 1 && data.deviceSlotIndex <= 8))
    {
        printf("The Device Slot Index is Invalid.\n\n");
    }
    else if((data.timeSlotStart > data.timeSlotEnd) || (data.timeSlotStart == data.timeSlotEnd) || (data.timeSlotStart < 0 || data.timeSlotStart > 24) || (data.timeSlotEnd < 0 || data.timeSlotEnd > 24))
    {
        printf("Invalid Time.\n\n");
    }
    else if((data.withVRHeadset < 0) || (data.withVRHeadset > 1))
    {
        printf("Invalid Input.\n\n");
    }
    else
    {
        strcpy(slots[slotCount].customerName, data.customerName);
        slots[slotCount].deviceSlotIndex = data.deviceSlotIndex;
        slots[slotCount].timeSlotStart = data.timeSlotStart;
        slots[slotCount].timeSlotEnd = data.timeSlotEnd;
        slots[slotCount].withVRHeadset = data.withVRHeadset;
        fprintf(fp, "%s, %d, %d, %d, %d\n", data.customerName, data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd, data.withVRHeadset);
        printf("Booking Successful.\n\n");
    }
    fclose(fp);
}

void loadGameList()
{
    FILE *fp;
    fp = fopen("gameList.txt", "r+");
    if(fp == NULL)
    {
        printf("File Does Not Exist.\n");
        return;
    }
    char gameName[100], gameCategory[100];
    printf("----------- GameCafe Slot Management -----------\n\n");
    printf("Game List (Name, Category):\n\n");
    while(fscanf(fp, " %[^|]|%[^\n]", gameCategory, gameName) == 2)
        {
           printf("%s, %s\n\n", gameName, gameCategory);
        }
    printf("\n");
}

void editSlotBooking()
{
    char customerName[100];
    int deviceIndex;
    int startingTime;
    printf("Enter Customer Name: ");
    getchar();
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';
    printf("Enter Device Index: ");
    scanf("%d", &deviceIndex);
    printf("Enter Slot Starting Time (Only the Hours in 24 Hrs Format): ");
    scanf("%d", &startingTime);
    loadSlotDataFromFile();
    printf("\n");
    for(int i = 0; i < slotCount; i++)
    {
        if((strcmp(customerName, slots[i].customerName) == 0) && (deviceIndex == slots[i].deviceSlotIndex) && (startingTime == slots[i].timeSlotStart))
        {
            int previousDeviceSlot = slots[i].deviceSlotIndex;
            int previousStartingTime = slots[i].timeSlotStart;
            int previousEndingTime = slots[i].timeSlotEnd;
            Prompt:
            printf("1. Edit Customer Name.\n");
            printf("2. Change Device Slot.\n");
            printf("3. Change the Starting & Ending Time of the Session.\n");
            printf("4. Equip or Unequip VR Addon.\n");
            printf("5. Ended up Editing the Slot.\n");
            int options;
            printf("Select an Option. Enter 1/2/3/4/5: ");
            scanf("%d", &options);
            switch(options)
            {
                case 1:
                    char anotherCustomerName[50];
                    printf("Enter the Name to Replace with: ");
                    getchar();
                    fgets(anotherCustomerName, sizeof(anotherCustomerName), stdin);
                    anotherCustomerName[strcspn(anotherCustomerName, "\n")] = '\0';
                    strcpy(slots[i].customerName, anotherCustomerName);
                    printf("\n");
                    goto Prompt;
                    break;
                case 2:
                    int anotherSlotIndex;
                    printf("Enter a Slot Index to Replace with: ");
                    scanf("%d", &anotherSlotIndex);
                    slots[i].deviceSlotIndex = anotherSlotIndex;
                    printf("\n");
                    goto Prompt;
                    break;
                case 3:
                    int timeStart, timeEnd;
                    printf("Enter a New Time to Start the Session (Only the Hours in 24 Hrs Format): ");
                    scanf("%d", &timeStart);
                    printf("Enter a New Time to End the Session (Only the Hours in 24 Hrs Format): ");
                    scanf("%d", &timeEnd);
                    slots[i].timeSlotStart = timeStart;
                    slots[i].timeSlotEnd = timeEnd;
                    printf("\n");
                    goto Prompt;
                    break;
                case 4:
                    int VR;
                    printf("Enter 1 if You Want to Use VR, else Enter 0: ");
                    scanf("%d", &VR);
                    slots[i].withVRHeadset = VR;
                    printf("\n");
                    goto Prompt;
                    break;
                case 5:
                    break;
                default:
                    printf("Invalid Input.\n");
                    goto Prompt;
            }
            if((slots[i].deviceSlotIndex == previousDeviceSlot) && (slots[i].timeSlotStart >= previousStartingTime) && (slots[i].timeSlotEnd >= previousEndingTime))
            {
                printf("Booking Updated.\n\n");
                FILE *fp;
                fp = fopen("slotData.txt", "w+");
                fprintf(fp, "");
                fclose(fp);
                fp = fopen("slotData.txt", "a");
                for(int i = 0; i < slotCount; i++)
                    {
                        fprintf(fp, "%s, %d, %d, %d, %d\n", slots[i].customerName, slots[i].deviceSlotIndex, slots[i].timeSlotStart, slots[i].timeSlotEnd, slots[i].withVRHeadset);
                    }
                fclose(fp);
                return;
            }
            else if((checkIfSlotIsBooked(slots[i].deviceSlotIndex, slots[i].timeSlotStart, slots[i].timeSlotEnd) != 1) && (slots[i].timeSlotStart < slots[i].timeSlotEnd))
            {
                printf("Booking Updated.\n\n");
                FILE *fp;
                fp = fopen("slotData.txt", "w+");
                fprintf(fp, "");
                fclose(fp);
                fp = fopen("slotData.txt", "a");
                for(int i = 0; i < slotCount; i++)
                    {
                        fprintf(fp, "%s, %d, %d, %d, %d\n", slots[i].customerName, slots[i].deviceSlotIndex, slots[i].timeSlotStart, slots[i].timeSlotEnd, slots[i].withVRHeadset);
                    }
                fclose(fp);
                return;
            }
            else
            {
                printf("Invalid Input or Another Slot is Already Booked at the New Time.\n\n");
                goto Prompt;
            }
        }
    }
    return;
}

void showAllSlotData()
{
    struct slotCustomerData data;
    FILE *fp;
    fp = fopen("slotData.txt", "r+");
    if(fp == NULL)
    {
        return;
    }
    printf("\n");
    int TotalRent = 0;
    while(fscanf(fp, " %[^,], %d, %d, %d, %d", data.customerName, &data.deviceSlotIndex, &data.timeSlotStart, &data.timeSlotEnd, &data.withVRHeadset) == 5)
    {
        printf("Name: %s \nDevice Index: %d \nTime Slot: %d:00 - %d:00\n", data.customerName, data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd);
        if(data.withVRHeadset == 1)
        {
            printf("With VR: Yes\n");
        }
        else
        {
            printf("With VR: No\n");
        }
        TotalRent += calculateRent(data);
        printf("Rent: %d Taka", calculateRent(data));
        printf("\n\n");
    }
    printf("Total Rent: %d Taka", TotalRent);
    fclose(fp);
    printf("\n\n");
}

void showAllSlotBriefInfo()
{
    struct slotCustomerData data;
    FILE *fp;
    fp = fopen("slotData.txt", "r");
    if(fp == NULL)
    {
        return;
    }
    while(fscanf(fp, " %[^,], %d, %d, %d, %d", data.customerName, &data.deviceSlotIndex, &data.timeSlotStart, &data.timeSlotEnd, &data.withVRHeadset) == 5)
    {
        printf("Name: %s\nDevice Index: %d\nTime Slot: %d:00 - %d:00\nRent: %d Taka\n\n", data.customerName, data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd, calculateRent(data));
    }
    fclose(fp);
}

int calculateRent(struct slotCustomerData data)
{
    int rent;
    if(data.withVRHeadset == 1)
    {
        rent = (data.timeSlotEnd - data.timeSlotStart) * 150;
    }
    else
    {
        rent = (data.timeSlotEnd - data.timeSlotStart) * 100;
    }
    return rent;
}

void searchCustomerName()
{
    struct slotCustomerData data;
    FILE *fp;
    FILE *temporaryfp;
    char customerName[100];
    int found = 0;
    printf("Enter Customer Name to Search Booking: ");
    getchar();
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';
    fp = fopen("slotData.txt", "r");
    if(fp == NULL)
    {
        printf("File does not exist.\n");
        return;
    }
    printf("\n");
    while(fscanf(fp, " %[^,], %d, %d, %d, %d", data.customerName, &data.deviceSlotIndex, &data.timeSlotStart, &data.timeSlotEnd, &data.withVRHeadset) == 5)
    {
        if(strcmp(data.customerName, customerName) == 0)
        {
            found = 1;
            printf("Name: %s\nDevice Index: %d\nTime Slot: %d:00 - %d:00\n", data.customerName, data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd);
            if(data.withVRHeadset == 1)
            {
                printf("With VR: Yes\n\n");
            }
            else
            {
                printf("With VR: No\n\n");
            }
        }
        void loadSlotDataFromFile();
    }
    if (!found)
    {
        printf("The Customer '%s' is not found.\n\n", customerName);
    }
    fclose(fp);
}

void cancelSlotBooking()
{
    struct slotCustomerData data;
    FILE *fp;
    FILE *temporaryfp;
    char customerName[100];
    int found = 0;
    printf("Enter Customer Name to Cancel Booking: ");
    getchar();
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';
    fp = fopen("slotData.txt", "r");
    temporaryfp = fopen("tempSlotData.txt", "w");
    if(fp == NULL || temporaryfp == NULL)
    {
        printf("File does not exist.\n");
        return;
    }
    while(fscanf(fp, " %[^,], %d, %d, %d, %d", data.customerName, &data.deviceSlotIndex, &data.timeSlotStart, &data.timeSlotEnd, &data.withVRHeadset) == 5)
    {
        if(strcmp(data.customerName, customerName) != 0)
        {
            fprintf(temporaryfp, "%s, %d, %d, %d, %d\n", data.customerName, data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd, data.withVRHeadset);
        }
        else
        {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temporaryfp);
    if(found == 1)
    {
        fp = fopen("slotData.txt", "w");
        temporaryfp = fopen("tempSlotData.txt", "r");
        if(fp == NULL || temporaryfp == NULL)
        {
            printf("File does not exist.\n");
            return;
        }
        while(fscanf(temporaryfp, " %[^,], %d, %d, %d, %d", data.customerName, &data.deviceSlotIndex, &data.timeSlotStart, &data.timeSlotEnd, &data.withVRHeadset) == 5)
        {
            fprintf(fp, "%s, %d, %d, %d, %d\n", data.customerName, data.deviceSlotIndex, data.timeSlotStart, data.timeSlotEnd, data.withVRHeadset);
        }
        void loadSlotDataFromFile();
        printf("Slot Booked for '%s' Has Been Cancelled Successfully.\n\n", customerName);
        fclose(fp);
        fclose(temporaryfp);
    }
    else
    {
        printf("The Customer '%s' Could not be found.\n\n", customerName);
    }
}

int checkIfSlotIsBooked(int deviceSlotIndex, int timeSlotStart, int timeSlotEnd)
{
    struct slotCustomerData data;
    FILE *fp;
    fp = fopen("slotData.txt", "r");
    if(fp == NULL)
    {
        return 0;
    }
    while(fscanf(fp, " %[^,], %d, %d, %d, %d", data.customerName, &data.deviceSlotIndex, &data.timeSlotStart, &data.timeSlotEnd, &data.withVRHeadset) == 5)
    {
        if(data.deviceSlotIndex == deviceSlotIndex)
        {
            if((timeSlotStart < data.timeSlotEnd) && (timeSlotEnd > data.timeSlotStart))
            {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}
