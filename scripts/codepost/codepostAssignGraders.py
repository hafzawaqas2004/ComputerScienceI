"""
This script interfaces with canvas and codepost.io to
  1. Consolidate assignment pairs based on pairings in canvas
     -to reduce grading burden and improve consistency
     -we use canvas pairs instead of codepost "partners" as
      codepost's mechanism is clunky (must be done on
      every assignment via sending a URL/hash to partner).
      Codepost also only allows groups of arbitrary size;
      canvas can be limited to groups of 2 (and they can
      join/leave at will)
  2. Assign graders in codepost to the individuals/pairs
     for grading
     -It randomizes grading assignments (evenly distributing
      them among graders) and outputs an assignment report to
      the standard output and produces a CSV file (for QC)

TODO: needs troubleshooting
"""
import argparse
import codepost
import sys
import pprint
from config import config
from course import course
from codepostUtils import get_assignment_id

parser = argparse.ArgumentParser()
parser.add_argument("--commit", action='store_true', help=
  """Commit the pair consolidation and grader assignments
  to codepost. By default, no action is taken, only a report
  is made.
  """)
parser.add_argument("codepost_assignment_name", help=
  """The codepost.io assignment name (the ID is retrieved
  using this name)
  """)
args = parser.parse_args()

codepost_assignment_name = args.codepost_assignment_name
codepost_assignment_id = get_assignment_id(codepost_assignment_name)
commit_to_codepost = args.commit

if codepost_assignment_id is None:
    print(f"Codepost assignment for '{codepost_assignment_name}' not found", file=sys.stderr)
    exit(1)

def consolidateAndAssign(gradingAssignment):
    """
    Consolidates partners/pairs in codepost based on the
    `grading_group_name` in Canvas (see `config.py`)

    In codepost, a student can only be associated with *one*
    submission.  We cannot consolidate if both have submitted, so:
      - if neither have submitted, it is ignored
      - if one or the other (xor) but not both have submitted, we
        consolidate to the one submission
      - if both have submitted, we prefer the first and delete the
        second
    """
    # get all submissions for an assignment directly
    print(f"Consolidating pairs and assigning graders...")
    assignment_submissions = codepost.assignment.list_submissions(id=codepost_assignment_id)
    print(f"    {len(assignment_submissions)} submissions...")
    for grader,groups in gradingAssignment.items():
        for group in groups:
            # get submission associated with first member:
            submissionA = next( (s for s in assignment_submissions if group.members[0].canvasEmail in s.students), None)
            submissionB = next( (s for s in assignment_submissions if group.members[1].canvasEmail in s.students), None)
            graderEmail = grader.canvasEmail
            print(f"Processing group:")
            print(f"{group}")
            submission = None
            deleteSubmission = None
            if submissionA is None and submissionB is None:
                print(f"    No submission (neither)!")
            elif submissionA is None or submissionB is None:
                #only 1 submission; use it, no need to delete
                submission = submissionA if submissionA is not None else submissionB
            else:
                #two submissions; we prefer A over B and delete B
                submission = submissionA
                deleteSubmission = submissionB
            if submission is not None:
                codepostStudentGroup = [group.members[0].canvasEmail]
                print(f"    Assigning {graderEmail} to group {group.canvasGroupName}...")
                if len(group) > 1:
                    print(f"    Consolidating {group.members[1].canvasEmail} to {group.members[0].canvasEmail}...")
                    codepostStudentGroup.append(group.members[1].canvasEmail)
                    if deleteSubmission is not None:
                        print(f"    Deleting submission {deleteSubmission.id} by {deleteSubmission.students}, yeehaw...")
                if commit_to_codepost:
                    if deleteSubmission is not None:
                        codepost.submission.delete(id=deleteSubmission.id)
                    codepost.submission.update(id=submission.id, grader=graderEmail, students=studentGroup)

print(f"Processing codepost assignment '{codepost_assignment_name}' (id={codepost_assignment_id})...")
if not commit_to_codepost:
    print(f"    Coward Mode...");

# Formulate a grading assignment, load from canvas/groups
gradingAssignment = course.getGradingAssignment()
s = course.assignmentToString(gradingAssignment)
print(s)

# dump to CSV for
csv = course.assignmentToCSV(gradingAssignment)
csvFile = f"./{codepost_assignment_name.replace(' ', '_')}_{codepost_assignment_id}.csv"
f = open(csvFile, "w")
f.write(csv)
f.close()

consolidateAndAssign(gradingAssignment)

if not commit_to_codepost:
    print("Cowardly refusing to commit any changes to codepost.io; rerun with --commit when you are braver.")
