import pygsheets

gc = pygsheets.authorize()

sh = gc.open_by_key('18oxkrFKQqETnOmNAx0y2SrPGH0LMOrvVZQsFpxPvKO8')

wks = sh.sheet1

a1 = wks.cell('A1')

print a1
