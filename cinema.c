#include <stdio.h>

#define max 10
#define r 8
#define c 10
#define maxb 80

typedef struct {
    int   id;
    char  name[50];
    char  phone[13];
    int   count;
    int seats[r][c];
}Booking;

int getPrice(int row){
    if(row<3)
        return 150;
    if(row<7)
        return 350;
    return 650;
}

int bookingCost(Booking b){
    int total=0;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(b.seats[i][j]==1)
            total=total+getPrice(i);
        }
    }
    return total;
}

void printBooking(Booking b){
    printf("\nBooking ID : %d\n",b.id);
    printf("Name       : %s\n",b.name);
    printf("Phone      : %s\n",b.phone);
    printf("Tickets    : %d\n",b.count);
    printf("Seats      : ");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(b.seats[i][j]==1)
            printf("%d-%d  ",i+1,j+1);
        }
    }
    printf("\nTotal Cost : Rs. %d\n",bookingCost(b));
}

void displaySeating(int a[r][c]){
    printf("   Movie Name: Intersteller | Screen 1 | 7:30 PM\n\n");
    printf("            ===== S C R E E N =====\n");
    printf("     1    2    3    4    5    6    7    8    9   10 \n\n");
    for(int i=0;i<r;i++){
        if(i==0)
        printf("=======================SILVER RS. 150===================\n\n");
        if(i==3)
        printf("========================GOLD RS. 350====================\n\n");
        if(i==7)
        printf("======================PLATINUM RS. 650===================\n\n");
        for(int j=0;j<c;j++){
            if(a[i][j]==0)
            printf(" [ ] ");
            if(a[i][j]==1)
            printf(" [X] ");
        }
        printf(" Row %d \n\n",1+i);
    }
    printf("[ ]=Available [X]=Already Booked\n");
}

void displayAvailabilty(int a[r][c]){
    printf("\n=========== AVAILABLE SEATS (row-column) ===========\n");
    printf("SILVER:\n");
    for(int i=0;i<3;i++){
        for(int j=0;j<c;j++){
            if(a[i][j]==0)
            printf("%d-%d ",i+1,j+1);
        }
        printf("\n");
    }
    printf("GOLD:\n");
    for(int i=3;i<7;i++){
        for(int j=0;j<c;j++){
            if(a[i][j]==0)
            printf("%d-%d ",i+1,j+1);
        }
        printf("\n");
    }
    printf("PLATINUM:\n");
    for(int i=7;i<=7;i++){
        for(int j=0;j<c;j++){
            if(a[i][j]==0)
            printf("%d-%d ",i+1,j+1);
        }
        printf("\n");
    }
}

void bookSeats(int a[r][c], Booking list[], int *total){
    Booking b;
    int free=0;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            b.seats[i][j]=0;
        }
    }

    if(*total>=maxb){
        printf("Booking list is full\n");
        return;
    }
    printf("Enter your Name:\n");
    scanf("%s",b.name);
    printf("Enter your Phone Number:\n");
    scanf("%s",b.phone);
    printf("Enter No. of tickets(MAX:10):");
    scanf("%d", &b.count);

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(a[i][j]==0)
            free++;
        }
    }

    if(b.count >= 1 && b.count <= max)
    {
        if(b.count>free){
            printf("Not enough seats available\n");
            return;
        }
        printf("Enter seat numbers: %s\n",b.name);
        for(int k=0;k<b.count;k++){
            int row,col;
            printf("Ticket %d - Enter row (1-8): ",k+1);
            scanf("%d",&row);
            printf("Ticket %d - Enter column (1-10): ",k+1);
            scanf("%d",&col);
            if(row<1 || row>r || col<1 || col>c){
                printf("Invalid seat, try again\n");
                k--;
            }
            else if(a[row-1][col-1]==1){
                printf("Seat already booked, try again\n");
                k--;
            }
            else{
                a[row-1][col-1]=1;
                b.seats[row-1][col-1]=1;
            }
        }
        b.id=*total+1;
        list[*total]=b;
        *total=*total+1;
        printf("\nBooking successful!");
        printBooking(b);
    }
    else
    printf("No. of tickets exceed MAX");
}

void cancelBooking(int a[r][c], Booking list[], int total){
    int id;
    printf("Enter Booking ID to cancel: ");
    scanf("%d",&id);
    if(id<1 || id>total || list[id-1].count==0){
        printf("Booking not found\n");
        return;
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(list[id-1].seats[i][j]==1){
                a[i][j]=0;
                list[id-1].seats[i][j]=0;
            }
        }
    }
    list[id-1].count=0;
    printf("Booking %d cancelled\n",id);
}

void calculateCost(Booking list[], int total){
    int id;
    printf("Enter Booking ID: ");
    scanf("%d",&id);
    if(id<1 || id>total || list[id-1].count==0){
        printf("Booking not found\n");
        return;
    }
    printf("Total cost for booking %d = Rs. %d\n",id,bookingCost(list[id-1]));
}

void displayAll(Booking list[], int total){
    int found=0;
    for(int k=0;k<total;k++){
        if(list[k].count>0){
            printBooking(list[k]);
            found=1;
        }
    }
    if(found==0)
    printf("No bookings yet\n");
}

void searchBooking(Booking list[], int total){
    int ch;
    int found=0;
    printf("1. Search by Booking ID\n");
    printf("2. Search by Seat number\n");
    printf("Enter choice: ");
    scanf("%d",&ch);
    if(ch==1){
        int id;
        printf("Enter Booking ID: ");
        scanf("%d",&id);
        if(id>=1 && id<=total && list[id-1].count>0){
            printBooking(list[id-1]);
            found=1;
        }
    }
    else if(ch==2){
        int row,col;
        printf("Enter row (1-8): ");
        scanf("%d",&row);
        printf("Enter column (1-10): ");
        scanf("%d",&col);
        if(row>=1 && row<=r && col>=1 && col<=c){
            for(int k=0;k<total;k++){
                if(list[k].seats[row-1][col-1]==1){
                    printBooking(list[k]);
                    found=1;
                }
            }
        }
    }
    if(found==0)
    printf("No booking found\n");
}

void generateTicket(Booking list[], int total){
    int id;
    printf("Enter Booking ID: ");
    scanf("%d",&id);
    if(id<1 || id>total || list[id-1].count==0){
        printf("Booking not found\n");
        return;
    }
    printf("\n************ TICKET / RECEIPT ************\n");
    printf("Movie : Intersteller | Screen 1 | 7:30 PM");
    printBooking(list[id-1]);
    printf("******** Enjoy your movie! ********\n");
}

void saveToFile(Booking list[], int total){
    FILE *fp;
    fp=fopen("bookings.txt","w");
    if(fp==NULL){
        printf("Could not open file\n");
        return;
    }
    for(int k=0;k<total;k++){
        if(list[k].count>0){
            fprintf(fp,"ID: %d | Name: %s | Phone: %s | Tickets: %d | Cost: Rs. %d | Seats: ",
                    list[k].id,list[k].name,list[k].phone,list[k].count,bookingCost(list[k]));
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    if(list[k].seats[i][j]==1)
                    fprintf(fp,"%d-%d ",i+1,j+1);
                }
            }
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
    printf("Bookings saved to bookings.txt\n");
}

int main(){
    int arr[r][c];
    Booking list[maxb];
    int total=0;
    int choice=6484860;

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            arr[i][j]=0;
        }
    }

    while(choice!=0){

    printf("\n=========== CINEMA SEAT BOOKING ===========\n");
    printf("  1. Display seating arrangement\n");
    printf("  2. Display available seats\n");
    printf("  3. Book seat(s)\n");
    printf("  4. Cancel a booking\n");
    printf("  5. Calculate ticket cost\n");
    printf("  6. Display all booking details\n");
    printf("  7. Search booking (ID or seat number)\n");
    printf("  8. Generate ticket / receipt\n");
    printf("  9. Save booking information to file\n");
    printf("  0. Exit\n");
    printf("============================================\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            displaySeating(arr);
            break;
        case 2:
            displayAvailabilty(arr);
            break;
        case 3:
            bookSeats(arr,list,&total);
            break;
        case 4:
            cancelBooking(arr,list,total);
            break;
        case 5:
            calculateCost(list,total);
            break;
        case 6:
            displayAll(list,total);
            break;
        case 7:
            searchBooking(list,total);
            break;
        case 8:
            generateTicket(list,total);
            break;
        case 9:
            saveToFile(list,total);
            break;
        case 0:
            printf("Thank you! Goodbye.\n");
            break;
        default:
            printf("Invalid choice\n");
        }

    }
    return 0;
}
