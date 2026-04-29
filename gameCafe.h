#ifndef GAMECAFE_H_INCLUDED
#define GAMECAFE_H_INCLUDED

struct slotCustomerData
{
    char customerName[100];
    int deviceSlotIndex;
    int timeSlotStart;
    int timeSlotEnd;
    int withVRHeadset;
};

struct AdminUserData
{
    char username[50];
    char pass[50];
};

struct slotCustomerData inputSlotData();
void saveSlotData(struct slotCustomerData data);
void loadGameList();
void loadSlotDataFromFile();
void showAllSlotData();
void showAllSlotBriefInfo();
int calculateRent(struct slotCustomerData data);
void editSlotBooking();
int checkUserPass();
void changeAdminPassword();
void registerAnotherAdmin();
void searchCustomerName();
void cancelSlotBooking();
int checkIfSlotIsBooked(int deviceSlotIndex, int timeSlotStart, int timeSlotEnd);

#endif // GAMECAFE_H_INCLUDED
