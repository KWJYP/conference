<?
session_start();
$_SESSION['test'] = $_POST["userid"]; 
?>
<?
include("db_inform.php");
include("main.php");
function login_check($conn,$sql)
{	
	$result = mysqli_query($conn,$sql);
	$fuserid=$_POST["userid"];
	$fuserpw=$_POST["userpw"];
	while($row = mysqli_fetch_array($result,MYSQLI_NUM))
	{
	if(strcmp($fuserid,$row[0])==0)
	{
#		printf("Login 상태");
		break;
	}
	else
	{
		$sql = "insert into LOGIN(id,pwd) values(
                       '$fuserid','$fuserpw')";
                       mysqli_query($conn,$sql);
	#	echo "TABLE 추가";
	}	
	}
}
$flag =0;
$sql = "select id,pwd from USER";
$result = mysqli_query($conn, $sql);
$userid = $_POST["userid"];
$userpw = $_POST["userpw"];
while($row = mysqli_fetch_array($result,MYSQLI_NUM))
{
	if(strcmp($userid,$row[0])==0)
	{
		if(strcmp($userpw,$row[1])==0)
		{
		$_SESSION['id']=$userid;
		$_SESSION['pw']=$userpw;	
		echo $_session['id'];
		$sql = "select * from LOGIN";
		$result = mysqli_query($conn,$sql);
		if(!mysqli_num_rows($result))
		{
	#	printf("로그인 table 생성!");
		$sql = "create table LOGIN(
       			id varchar(30),
       			pwd varchar(20))";
        		mysqli_query($conn, $sql);
		$sql = "insert into LOGIN(id,pwd) values(
			'$userid','$userpw')";
			mysqli_query($conn,$sql);
		echo "<script>alert(\"로그인 성공!\");</script>";
		echo "<script>document.location.replace('loginpage.htm')</script>";
		$flag = 1;
		}
		else
		{
		login_check($conn,$sql);
		echo "<script>alert(\"로그인 성공!\");</script>";
		echo "<script>document.location.replace('loginpage.htm')</script>";
		$flag =1;
		}
		break;
		}
	}
}
if($flag == 0)
{
echo "<script>alert(\"로그인 실패\");</script>";
echo "<script>document.location.replace('main.php')</script>";
}
mysqli_free_result($result);
mysqli_close($conn);

?>
