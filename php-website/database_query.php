<?php
require_once(dirname(__FILE__). "\database_connect.php");
// windows path
 
$sql = "SELECT * FROM usertable";
echo "<table align=\"left\" cellspacing=\"5\" cellpadding=\"8\">
<tr><td align=\"left\"><b>ID</b></td>
<td align=\"left\"><b>First Name</b></td>
<td align=\"left\"><b>Last Name</b></td>
<td align=\"left\"><b>Email</b></td>
<td align=\"left\"><b>Home Address</b></td>
<td align=\"left\"><b>Home Phone</b></td>
<td align=\"left\"><b>Cell Phone</b></td></tr>";
foreach($conn->query($sql) as $row){
	echo "<tr><td align=\"left\">" .
		$row["id"] . "</td><td align=\"left\">" .
		$row["First Name"] ."</td><td align=\"left\">" .
		$row["Last Name"] ."</td><td align=\"left\">" .
		$row["Email"] ."</td><td align=\"left\">" .
		$row["Home Address"] ."</td><td align=\"left\">" .
		$row["Home Phone"] ."</td><td align=\"left\">" .
		$row["Cell Phone"] ."</td><td align=\"left\">" ;
	echo "</tr>";
}
echo "</table>";

$conn = null;

?>
