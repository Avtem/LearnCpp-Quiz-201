#singleInstance Force
MAX_STEP_NR := 4

Gui, Add, Text    , x16 y16 w120 h20, &Choose the step number:
Gui, Add, Edit    , x156 y16 w70 h30 vedit -Multi +Number -VScroll +Vertical
Gui, Add, UpDown  , x226 y16 w20 h30 range1-%MAX_STEP_NR%
Gui, Add, CheckBox, x156 y46 w90 h30 gBoxEntireSol vBoxEntireSol, &Entire solution
Gui, Add, Button  , x16 y86 w230 h30 default ggenerate, &Generate code and copy to clipboard

; Generated using SmartGUI Creator 4.0
Gui, Show, h139 w274, Code generator
Return

GuiClose:
ExitApp

BoxEntireSol:
guiControlGet, checked_, , BoxEntireSol
guiControl % checked_ ? "Disable" : "Enable", edit 
return

generate:

guiControlGet, editVal, , edit
guiControlGet, entireSol, , BoxEntireSol
if(entireSol)
	editVal := MAX_STEP_NR
if(editVal > MAX_STEP_NR)
{
	msgbox % "Step lesson number is too big."
	return
}

code := ""
includes := ""
loop % editVal
{
	fileRead, txtStep, Step 0%a_index%.cpp
	includes .= extractIncludes(txtStep)
	code .= txtStep
}
fileRead, txtTest, Testcode 0%editVal%.cpp
includes .= extractIncludes(txtTest)
trimIncludesAndRemoveDups(includes)
clipboard := includes "`n" code "`n`n" txtTest

; show tooltip
tooltip % "The code was copied to the clipboard", 55, 85
sleep 1500
tooltip
return

extractIncludes(ByRef fileStr)
{
	includes := ""
	pattern := "^#include.*?`r?`n`r?`n" ; match all #includes until an empty line found
	pos := regexMatch(fileStr, pattern, includes)
	if(pos)
		fileStr := subStr(fileStr, strLen(includes)) ; erase includes from entire file

	return includes
}

trimIncludesAndRemoveDups(ByRef includes)
{
	arr := strSplit(includes, "`n", "`r")
	
	; remove empty lines
	arrLen := arr.Length()
	loop % arrLen
	{
		i := arrLen - (a_index-1) ; reverse index
		if(arr[i] == "")
			arr.removeAt(i)
	}
	
	Sort, arr, u
	
	For Index, value In arr
		str .= value . "`n"
	
	includes := str
}