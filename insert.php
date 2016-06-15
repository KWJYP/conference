<?php
include ("db_inform.php");
#$conn = mysqli_connect("127.0.0.1","root","st951235","inform");
#if(mysqli_connect_errno()){
#        printf("[%d]connect failed : %s\n",mysqli_connect_errno(), mysqli_connect_error());
#        exit();
#}
$sql = "select * from USER";
$result = mysqli_query($conn,$sql);
if(mysqli_num_rows($result))
{
#        printf("고객 테이블 %d개 검색 성공!<br>", mysqli_affected_rows($conn));
}
else{
 #       printf("고객 테이블 검색 실패!<br>[%d]%s",mysqli_errno($conn),mysqli_error($conn));
        $sql = "create table USER(
        id varchar(30),
        pwd varchar(20),
        pwd_re varchar(20),
        name varchar(10),
        addr varchar(80),
        sex varchar(3),
        age int(2),
        email varchar(20))";
      	mysqli_query($conn,$sql);
}
$id=$_POST["id"];
$pwd = $_POST["pwd"];
$pwd_re=$_POST["pwd_re"];
$name=$_POST["name"];
$addr=$_POST["addr"];
$sex=$_POST["sex"];
$age=$_POST["age"];
$email=$_POST["email"];
echo "$id,$pwd,$pwd_re,$name,$addr,$sex,$age,$email";
$sql="INSERT INTO USER VALUES('$id','$pwd','$pwd_re','$name','$addr','$sex','$age','$email')";
mysqli_query($conn,$sql);

while($customer = mysqli_fetch_array($result))
{
        printf("%s %s %s %s %s %s %d %s\n",$customer["id"],$customer["pwd"],$customer["pwd_re"],$customer["name"],$customer["addr"],$customer["sex"],$customer["age"],$customer["email"]);
}
	echo"<script>document.location.replace('main.php')</script>";
?>

                                                         
