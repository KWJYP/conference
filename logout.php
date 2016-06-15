<?
session_start();

#echo "<br>"; 
#echo $_SESSION['test']; 
$FLAG =$_SESSION['test'];
?>

<?
include("main.php");
include("db_inform.php");
$sql = "DELETE FROM LOGIN WHERE ID='$FLAG'";
$result = mysqli_query($conn,$sql);
mysqli_close();

echo "<script>alert(\"logout success!\");</script>";
echo "<script>document.location.replace('main.php')</script>";

?>
