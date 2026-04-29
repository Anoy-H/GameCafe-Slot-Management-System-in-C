#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameCafe.h"

int main()
{
    struct slotCustomerData data;
    int options;
    checkLoginCredinals:
    printf("----------- GameCafe Slot Management -----------\n\n");
    if(checkUserPass() != 1)
    {
        goto checkLoginCredinals;
    }
    printf("\n");
    loadSlotDataFromFile();
    do
    {
        printf("----------- GameCafe Slot Management -----------\n\n");
        printf("1. Book a Slot.\n");
        printf("2. Show All Booked Slot List.\n");
        printf("3. Search Booked Slot by Customer Name.\n");
        printf("4. Edit a Booked Slot.\n");
        printf("5. Cancel Booked Slot.\n");
        printf("6. Show Available Game List.\n");
        printf("7. Change Current Admin User Password.\n");
        printf("8. Register Another Admin User.\n");
        printf("9. Exit.\n\n");
        printf("Select an Option. Enter 1/2/3/4/5/6/7/8/9: ");
        scanf("%d", &options);
        printf("\n");
        switch(options)
        {
            case 1:
                data = inputSlotData();
                saveSlotData(data);
                break;
            case 2:
                showAllSlotData();
                break;
            case 3:
                searchCustomerName();
                break;
            case 4:
                editSlotBooking();
                break;
            case 5:
                cancelSlotBooking();
                break;
            case 6:
                loadGameList();
                break;
            case 7:
                changeAdminPassword();
                break;
            case 8:
                registerAnotherAdmin();
                break;
            case 9:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid Input.\n");
        }
    } while(options != 9);

    return 0;
}
