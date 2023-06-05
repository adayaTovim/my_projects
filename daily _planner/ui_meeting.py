import meeting as m


def print_menu():
    print("\033[1;29mMenu:\033[0m")
    print("\033[1;38m1. Add a meeting\033[0m")
    print("\033[1;38m2. Print meeting\033[0m")
    print("\033[1;38m3. Find meeting\033[0m")
    print("\033[1;38m4. Remove meeting\033[0m")
    print("\033[1;38m5. Exit\033[0m")
    result = int(input())
    return result
#............................................
def print_second_menu():
    print("\033[1;38m1. Print a single meeting\033[0m")
    print("\033[1;38m2. Print meetings in date\033[0m")
    print("\033[1;38m3. Print meetings of a specific participant\033[0m")
    print("\033[1;38m4. Print all meetings in the diary\033[0m")
    print("\033[1;38m5. Back to the main menu\033[0m")

    result = int(input())
    return result
#............................................
def get_name():
    name = input("Enter the name of meeting: ")
    if not name:
        raise ValueError("\033[91mName cannot be empty.\033[0m")
    name = name.title()
    return name
#............................................
def get_date():
    date = input("Enter the date of meeting in format DD.MM.YY: ")
    if len(date) != 8:
        raise ValueError("\033[91mInvalid date format. Correct format is DD.MM.YY.\033[0m")
    day, month, year = map(int, date.split("."))
    if not (1 <= day <= 31) or not (1 <= month <= 12) or not (23 <= year <= 99):
        raise ValueError("\033[91mInvalid date.\033[0m")
    if (year == 23 and month == 2 and day < 9) or year == 23 and month < 2:
        raise ValueError("\033[91mPast date.\033[0m")
    return date
#............................................
def get_start_time():
    time = input("Enter the start time in format HH:MM : ")
    if len(time) != 5:
        raise ValueError("\033[91mInvalid time format. Correct format is HH:MM.\033[0m")
    if time.isalpha():
        raise ValueError("\033[91mInvalid time.\033[0m")
    hour, minute = map(int, time.split(":"))
    if hour < 9 or hour > 18 or (hour == 17 and minute > 45):
        raise ValueError("\033[91mInvalid start time. Please enter between 9:00 and 17:45 .\033[0m")
    return time
#............................................
def get_end_time():
    time = input("Enter the end time in format HH:MM : ")
    if len(time) != 5:
        raise ValueError("\033[91mInvalid time format. Correct format is HH:MM.\033[0m")
    if time.isalpha():
        raise ValueError("\033[91mInvalid time.\033[0m")
    hour, minute = map(int, time.split(":"))
    if hour < 9 or hour > 18 or (hour == 9 and minute < 15):
        raise ValueError("\033[91mInvalid end time. Please enter between 9:15 and 18:00.\033[0m")
    return time
#..................................................
def get_participants():
    num = int(input("Enter the number of participants: "))
    i = 1
    selected_participants = []
    print("Choose participants from the following list: (Press enter between them)\n", m.all_participants)
    while i <= num:
        participant = input()
        participant = participant.title()
        if not participant.isalpha():
            raise ValueError("\033[91mInvalid participants.\033[0m")
        if participant not in m.all_participants:
            raise ValueError("\033[91mParticipants not found.\033[0m")
        selected_participants.append(participant)
        i += 1
    return selected_participants

