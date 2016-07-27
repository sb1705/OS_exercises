#https://pymotw.com/2/grp/

'''
Querying All Groups

Suppose you need to print a report of all of the “real” groups on a system, 
including their members (for our purposes, “real” is defined as having a name not starting with “_”). 
To load the entire password database, you would use getgrall(). 
The return value is a list with an undefined order, so you probably want to sort it before printing the report.

'''
import grp
import operator

# Load all of the user data, sorted by username
all_groups = grp.getgrall()
interesting_groups = sorted((g 
                            for g in all_groups 
                            if not g.gr_name.startswith('_')),
                            key=operator.attrgetter('gr_name'))

# Find the longest length for the name
name_length = max(len(g.gr_name) for g in interesting_groups) + 1

# Print report headers
fmt = '%-*s %4s %10s %s'
print fmt % (name_length, 'Name', 
             'GID', 
             'Password',
             'Members')
print '-' * name_length, '----', '-' * 10, '-' * 30

# Print the data
for g in interesting_groups:
    print fmt % (name_length, g.gr_name, 
                 g.gr_gid, 
                 g.gr_passwd,
                 ', '.join(g.gr_mem))

'''Group Memberships for a User

Another common task might be to print a list of all the groups for a given user:

'''

import grp

username = 'dhellmann'
groups = [g.gr_name for g in grp.getgrall() if username in g.gr_mem]
print username, 'belongs to:', ', '.join(groups)

'''
Finding a Group By Name

As with pwd, it is also possible to query for information about a specific group, either by name or numeric id.
'''

import grp

name = 'admin'
info = grp.getgrnam(name)
print 'Name    :', info.gr_name
print 'GID     :', info.gr_gid
print 'Password:', info.gr_passwd
print 'Members :', ', '.join(info.gr_mem)

'''
Finding a Group by ID

To identify the group running the current process, combine getgrgid() with os.getgid().

'''

import grp
import os

gid = os.getgid()
group_info = grp.getgrgid(gid)
print 'Currently running with GID=%s name=%s' % (gid, group_info.gr_name)



