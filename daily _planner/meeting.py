import ui_meeting as ui

all_rooms = ("room A","room B", "room C", "room D", "room E")
all_participants = ("Adaya", "Or", "Hadar", "Ori", "Rotem", "Lev", "Inbal", "Tomer", "Amitai", "Udi", "Matanel", "Lena", "Chaya")
meetings_diary = []


def add_meeting(meetings_diary, meeting_name, date, start_time, end_time, participants):
    """
    Add meeting to the meetings_diary list.
    :param meetings_diary: A list of dictionaries representing the existing meetings.
    :param meeting_name: A string representing the name of the meeting to be added.
    :param start_time: A string in the format "HH:MM" representing the start time of the meeting.
    :param end_time: A string in the format "HH:MM" representing the end time of the meeting.
    :param participants: A list of strings representing the participants in the meeting.
    :param date: A string in the format "DD-MM-YYYY" representing the date of the meeting.
    :return: False: if the `meeting_name` and `start_time` already exists in the `meetings_diary`,
                    or if the `end_time` is before the `start_time`,
                    or if either `start_time` or `end_time` is outside the range of 9:00 to 18:00,
                    or if one or more participants are not available,
                    or if no room is available.
              Otherwise, the function returns True.
    """
    for meeting in meetings_diary:
        if meeting["meeting_name"] == meeting_name and meeting["date"] == date and meeting["start_time"] == start_time:
            raise ValueError("\033[91mMeeting with the same name and start time already exists\033[0m")
            return False
    result = check_meeting_time(start_time, end_time)
    if result == False:
        return False
    result2 = participants_available(meetings_diary, participants, start_time, end_time, date)
    if result2 == False:
        raise ValueError("\033[91mParticipants are not available\033[0m")
        return False
    room = check_room_availability(meetings_diary, start_time, end_time, date)
    if room == None:
        raise ValueError("\033[91mNo room is available\033[0m")
        return False

    meeting = {
        "meeting_name": meeting_name,
        "date": date,
        "start_time": start_time,
        "end_time": end_time,
        "participants": participants,
        "room": room
    }
    meetings_diary.append(meeting)
    return True
#.......................................................................
def print_meeting(meetings_diary, meeting_name, start_time,date):
    """
    Prints a one meeting
    :param meetings_diary: A list of dictionaries representing the existing meetings.
    :param meeting_name: A string representing the name of the meeting to be added.
    :param start_time: A string in the format "HH:MM" representing the start time of the meeting.
    :param date: A string in the format "DD-MM-YYYY" representing the date of the meeting.
    :return:
    """
    if meeting_name is not None and start_time is not None and date is not None:
        for meeting in meetings_diary:
            if meeting["meeting_name"] == meeting_name and meeting["start_time"] == start_time and meeting["date"] == date:
                print("Meeting name:" ,meeting["meeting_name"])
                print("Date:", meeting["date"])
                print("Start time:" , meeting["start_time"])
                print("End time:" , meeting["end_time"])
                print("Participants:" , meeting["participants"])
                print("Room:" ,meeting["room"])
                print("---")
                return True
        raise ValueError("\033[91mMeeting not found\033[0m")
        return False
    else:
        raise ValueError("\033[91mMeeting name or start time is None\033[0m")
        return False
#........................................................

def print_meeting_by_type(meetings_diary, print_type, meeting_name, start_time, end_time, participant, date):
    """"
    print meetings according to a certain requirement
    :param meetings_diary: A list of dictionaries representing the existing meetings.
    :param meeting_name: A string representing the name of the meeting to be added. can be None
    :param start_time: A string in the format "HH:MM" representing the start time of the meeting. can be None
    :param end_time: A string in the format "HH:MM" representing the end time of the meeting. can be None
    :param participant: A list of strings representing the participants in the meeting. can be None
    :param date: A string in the format "DD-MM-YYYY" representing the date of the meeting.
    :return:
    """
    flag = 0
    if print_type == "single meeting":
        if True == print_meeting(meetings_diary, meeting_name, start_time,date):
            flag = 1
    elif print_type == "all":
        for meeting in meetings_diary:
            print_meeting(meetings_diary, meeting["meeting_name"], meeting["start_time"], meeting["date"])
            flag = 1
    elif print_type == "participant":
        for meeting in meetings_diary:
            if participant in meeting["participants"]:
                print_meeting(meetings_diary, meeting["meeting_name"], meeting["start_time"], meeting["date"])
                flag = 1
    elif print_type == "date":
        for meeting in meetings_diary:
            if meeting["date"] == date:
                print_meeting(meetings_diary, meeting["meeting_name"], meeting["start_time"], date)
                flag = 1
    if flag == 0:
        raise ValueError("\033[91mNo meeting to print\033[0m")
#...................................................................
def find_meeting(meetings_diary, meeting_name, date, start_time):
    """
    find meeting from meetings_diary list.
    :param meetings_diary: A list of dictionaries representing the existing meetings.
    :param meeting_name: A string representing the name of the meeting to be added.
    :param date: A string in the format "DD-MM-YYYY" representing the date of the meeting.
    :param start_time: A string in the format "HH:MM" representing the start time of the meeting.
    :return: meeting on success or None if meeting not found
    """
    for meeting in meetings_diary:
        if meeting["meeting_name"] == meeting_name and meeting["date"] == date and meeting["start_time"] == start_time:
            return meeting
    print("\033[91mMeeting not found\033[0m")
    return None
#....................................................................
def remove_meeting(meetings_diary, meeting_name, date, start_time):
    """
    remove meeting from meetings_diary list.
    :param meetings_diary: A list of dictionaries representing the existing meetings.
    :param meeting_name: A string representing the name of the meeting to be added.
    :param start_time: A string in the format "HH:MM" representing the start time of the meeting.
    :param date: A string in the format "DD-MM-YYYY" representing the date of the meeting.
    :return: False: if the `meeting_name` and `start_time` not found in the `meetings_diary`,
             True: on success
    """
    meeting = find_meeting(meetings_diary, meeting_name, date, start_time)
    if meeting == None:
        return False
    else:
        meetings_diary.remove(meeting)
        print("\033[92mMeeting removed successfully\033[0m")
        return True
#..............................................................
def run_meeting(meetings_diary):
    """
     running a meeting scheduler application
    :param meetings_diary: A list of dictionaries representing the existing meetings.
    :return:
    """
    while 1:
        try:
            result = ui.print_menu()
            if result == 1:
                name_meeting = ui.get_name()
                date = ui.get_date()
                start_time = ui.get_start_time()
                end_time = ui.get_end_time()
                selected_participants = ui.get_participants()
                if (True == add_meeting(meetings_diary, name_meeting, date, start_time, end_time,selected_participants)):
                    print("\033[92mMeeting successfully added!\033[0m")
                    print_meeting_by_type(meetings_diary, "single meeting", name_meeting, start_time, None, None, date)
            elif result == 2:
                choice = ui.print_second_menu()
                if choice == 1:
                    name_meeting = ui.get_name()
                    date = ui.get_date()
                    start_time = ui.get_start_time()
                    print_meeting_by_type(meetings_diary, "single meeting", name_meeting, start_time, None, None, date)
                elif choice == 2:
                    date = ui.get_date()
                    print_meeting_by_type(meetings_diary, "date", None, None, None, None, date)
                elif choice == 3:
                    selected_participants = ui.get_participants()
                    print_meeting_by_type(meetings_diary, "participant", None, None, None, selected_participants,None)
                elif choice == 4:
                    print_meeting_by_type(meetings_diary, "all", None, None, None, None,None)
                elif choice == 5:
                    continue
            elif result == 3:
                name_meeting = ui.get_name()
                date = ui.get_date()
                start_time = ui.get_start_time()
                find_meeting(meetings_diary, name_meeting, date, start_time)
                print_meeting_by_type(meetings_diary, "single meeting", name_meeting, start_time, None, None,date)
            elif result == 4:
                name_meeting = ui.get_name()
                date = ui.get_date()
                start_time = ui.get_start_time()
                remove_meeting(meetings_diary, name_meeting, date, start_time)
            elif result == 5:
                break
        except Exception as e:
            print(e)
    return True


#.....................HELP FUNCTION.............................
#...............................................................
def check_meeting_time(start_time, end_time):
    start_hour, start_min = [int(x) for x in start_time.split(":")]
    end_hour, end_min = [int(x) for x in end_time.split(":")]
    if end_hour < start_hour or (end_hour == start_hour and end_min <= start_min):
        print("\033[91mEnd time cannot be before start time\033[0m")
        return False
    return True
#........................................................................
def check_room_availability(meetings_diary, start_time, end_time, date):
    for room in all_rooms:
        available = True
        for existing_meeting in meetings_diary:
            if existing_meeting["room"] == room:
                if date == existing_meeting["date"]:
                    if start_time >= (existing_meeting["start_time"] and start_time < existing_meeting["end_time"]) or (end_time > existing_meeting["start_time"] and end_time <= existing_meeting["end_time"]):
                        available = False
                        break
        if available:
            return room
    return None
#...................................................................
def participants_available(meetings_diary, participants, start_time, end_time, date):
    for meeting in meetings_diary:
        for participant in participants:
            if participant in meeting["participants"]:
                meeting_start_time = meeting["start_time"]
                meeting_end_time = meeting["end_time"]
                if date == meeting["date"]:
                    if (start_time >= meeting_start_time and start_time < meeting_end_time) or (end_time > meeting_start_time and end_time <= meeting_end_time):
                        return False
    return True




