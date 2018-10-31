<?php
require_once(dirname(__FILE__). '\database_connect.php');
// windows path

$sql = "INSERT INTO `usertable` (`id`, `First Name`, `Last Name`, `Email`, `Home Address`, `Home Phone`, `Cell Phone`) VALUES (NULL, 'Caleb', 'Romero', 'mauris.Morbi@pedeultricesa.co.uk', '76-1945 Vehicula St.', '1-703-640-1080', '1-802-220-1049')";
//$conn->beginTransaction();
$conn->exec($sql);
/*$conn->exec('INSERT INTO usertable ('First Name', 'Last Name', 'Email', 'Home Address', 'Home Phone', 'Cell Phone')*/
	/*VALUES ('Kennan Higgins','Mauris.blandit.enim@felis.ca','Ap '#'722-1004 Imperdiet Ave','1-789-636-9180','1-862-380-7743')');*/
//$conn->commit();
echo 'Insert successfully.';
$conn = null;
?>
