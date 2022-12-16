# C Workshop on Linked-List and Structures

## Class Attendance System (CAS)

Course (Class):

| Field              | Type          |
| ------------------ | ------------- |
| Name               | String        |
| Professor          | String        |
| Number of Students | Integer       |
| Students List      | Linked-List   |
| Number of Sessions | Integer       |
| Attendance List    | []Linked-List |

Student:

| Field | Type   |
| ----- | ------ |
| Name  | String |
| ID    | String |

CAS can manage multiple classes for your university in each semester.
In the beginning, users must select a class from a given list of classes then they can manage the class students and their attendance.
Please note that users can add or remove classes so the classes list must be a linked-list.
The attendance list is an array of Linked List that has a single linked-list of students for each session.
In each session, the user adds the name of the percent's students into the session's linked-list.
The user can see the list of students and their percent's rate and if they didn't meet the 3/16 rule they must be purged from the students' list with a user's agreement.
CAS can save class information into files (one file for each class) for users then load them in its another run.
Please note that strings can at most have a size of 255.

First Step: Implement and Test a simple linked-list.
Second Step: Implement and Test a single class with its attendance. (based on linked-list of the first step)
Third Step: Implement the whole program.
Fourth Step: Add persistency into CAS with files.

Step by Step [Gist](https://gist.github.com/1995parham/12684919529a6f2181208888d5a52cc5).
