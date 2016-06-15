<?php
$conn = mysqli_connect("localhost","hdd","hdd","inform");
if(mysqli_connect_errno()){
	printf("[%d]connect failed : %s\n", mysqli_connect_errno(),mysqli_connect_error());
	exit();
}
?>
