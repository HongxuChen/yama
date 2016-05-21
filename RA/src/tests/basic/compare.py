#! /usr/bin/env python

import re
import subprocess


def read_intervals(fname):
    f = open(fname)
    intervals = {}
    intersections = []
    for line in f:
        m = re.search('(?<=label=\").+ \[.*\](?=\"])', line)
        if m is not None:
            x = m.group(0).split(' ')
            intervals[x[0]] = "".join(x[1:3])
        else:
            m = re.search('(?<=label=\")\[.*\](?=\"])', line)
            if m is not None:
                intersections.append(m.group(0))
    return {'vars': intervals, 'intersections': set(intersections)}


def check_vars(crop_intervals, cousot_intervals):
    print "Checking var intervals:"
    variables = {}
    for v in crop_intervals:
        variables[v] = {'crop': crop_intervals[v], 'cousot': None}
    for v in cousot_intervals:
        if v in variables:
            variables[v]['cousot'] = cousot_intervals[v]
        else:
            variables[v] = {'cousot': cousot_intervals[v], 'crop': None}

    equal = True
    for v, i in variables.iteritems():
        if i['crop'] != i['cousot']:
            if equal:
                print '%-30s - %25s - %s' % ("VAR", "CROP", "COUSOT")
            print '%-30s - %25s - %s' % (v, str(i['crop']), str(i['cousot']))
            equal = False
    if equal:
        print "\tSame result"


def check_intersections(crop_intervals, cousot_intervals):
    print "Checking intersections:"
    crop_diff = set(crop_intervals) - set(cousot_intervals)
    cousot_diff = set(cousot_intervals) - set(crop_intervals)

    if len(crop_diff) > 0 or len(cousot_diff) > 0:
        print "Differences between them: "
        print "\tCrop have: "  # , crop_diff
        for r in crop_diff:
            print "\t", r, "  "
        print "\tCousot have: ", cousot_diff
    else:
        print "\tSame result"


def check_intervals(crop_fname, cousot_fname):
    crop_intervals = read_intervals(crop_fname)
    cousotIntervals = read_intervals(cousot_fname)
    check_vars(crop_intervals['vars'], cousotIntervals['vars'])
    check_intersections(crop_intervals['intersections'], cousotIntervals['intersections'])


tests = ['t1.c', 't2.c', 't3.c', 't4.c', 't5.c', 't6.c', 't7.c']
for test in tests:
    subprocess.call("./single_run.py -ra-intra-crop " + test, shell=True, stdout=open('/tmp/log', "a"),
                    stderr=open('/tmp/log', "a"))
    subprocess.call("cp /tmp/foocgpos.dot /tmp/foocgpos." + test + ".crop.dot", shell=True)
    subprocess.call("./single_run.py -ra-intra-cousot " + test, shell=True, stdout=open('/tmp/log', "a"),
                    stderr=open('/tmp/log', "a"))
    subprocess.call("cp /tmp/foocgpos.dot /tmp/foocgpos." + test + ".cousot.dot", shell=True)

    print "Checking [", test, "]: "
    check_intervals('/tmp/foocgpos.' + test + '.crop.dot', '/tmp/foocgpos.' + test + '.cousot.dot')
    print "--------------------------------------------------------------------"
