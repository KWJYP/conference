<script>
function login()
{
	document.form.action="login.php";
	document.form.submit();
}
</script>
<html>
 <head><title>HDD</title></head>
  <body><center>
 <table><p> <h1>HDD</h1></p>
  <form name = "form" method = "post" >    
     <tr>
	<td>ID</td>
	<td><input type = "text" name = "userid"></td></tr><br>
      <tr>
      <td>PASSWORD</td>
      <td><input type = "password" name ="userpw"></td>
      <td><input type = "button" value ="로그인" onclick = "login()"></td><br>
      </tr>
     
     
<tr><td><a href = "signup.php">회원가입</a></td></tr>
  </form>
 </body>
</html>

