#!/usr/bin/python
###########################
#Author: liyao
#Usage: python plot_penalty_effect.py [penalty effect file name]
#Functionality: Visualize penalty value's effects on sentence correct rate, sentence correct rate, insertion error, deletion error.
###########################

import sys
import re
import matplotlib.pyplot as plt

if len(sys.argv) != 2:
    print("Usage: python [penalty effect file name]")
    sys.exit()
    

#A list of regular expressions, elements are, matching penalty line, sentence correctness line, word correctness line, respectively.
patterns = []
patterns.append(re.compile("penalty\s*=\s*(.*)$"))
patterns.append(re.compile("SENT:\s%Correct=(\d+\.\d+)\s\[.*\]$"))
patterns.append(re.compile("WORD:\s%Corr=(\d+\.\d+),\s\S+\s\[\S+,\sD=(\d+),\s\S+\sI=(\d+),\s\S+\]"))

penalty = []         #penalty values list
sent_corr = []       #sentence correctness rate list
word_corr = []       #word correctness rate list
deletion_num = []    #deletion number list
insertion_num = []   #insertion number list

#Open file
try:
    fd = open(sys.argv[1], 'r')
except IOError:
    print("Cannot open " + sys.argv[1])
    
while True:
    #Read three lines.
    line_penalty = fd.readline()
    line_sent = fd.readline()
    line_word = fd.readline()
    if len(line_penalty) == 0 or len(line_sent) == 0 or len(line_word) == 0:
        print("Leftover lines:\n" + line_penalty + line_sent + line_word)
        print("File process complete!")
        break;

    #Extract penalty value
    m = patterns[0].search(line_penalty)
    penalty.append(int(m.group(1)))
    
    #Extract sentence correctness rate
    m = patterns[1].search(line_sent)
    sent_corr.append(float(m.group(1)))

    #Extract word correctness rate,  deletion error, insertion error
    m = patterns[2].search(line_word)
    word_corr.append(float(m.group(1)))
    deletion_num.append(int(m.group(2)))
    insertion_num.append(int(m.group(3)))

fd.close()

#Plot 4 graphs
fig, ((plt_sent_corr, plt_word_corr), (plt_deletion_num, plt_insertion_num)) = plt.subplots(2, 2)
#plot sentence correctness rate
plt_sent_corr.plot(penalty, sent_corr)
plt_sent_corr.set_title("Sentence correctness")
plt_sent_corr.set_xlabel("penalty")
plt_sent_corr.set_ylabel("correct(%)")
#plot word correcteness rate
plt_word_corr.plot(penalty, word_corr)
plt_word_corr.set_title("Word correctness")
plt_word_corr.set_xlabel("penalty")
plt_word_corr.set_ylabel("correct(%)")
#deletion number
plt_deletion_num.plot(penalty, deletion_num)
plt_deletion_num.set_title("Number of deletion")
plt_deletion_num.set_xlabel("penalty")
plt_deletion_num.set_ylabel("number")
#insertion number
plt_insertion_num.plot(penalty, insertion_num)
plt_insertion_num.set_title("Number of insertion")
plt_insertion_num.set_xlabel("penalty")
plt_insertion_num.set_ylabel("number")

fig.suptitle(sys.argv[1], fontsize=20);
fig.show()

raw_input("Press any key to continue...")
