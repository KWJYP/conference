<script>
var cnt =0;
function check()
{
	var pwd = document.form.pwd.value;
	var pwd_re = document.form.pwd_re.value;
	if(cnt == 0)
	{
	if(pwd==pwd_re)
	{
	alert("비밀번호 확인");
	cnt=1;
	}
	else
	{
	alert("비밀번호를 확인해주세요");
	cnt=0;
	}
	}	
}
function insert()
{
if(cnt ==0)
{
alert("비밀번호 확인을 눌러주세요");
}
else
{
document.form.action ="insert.php";
document.form.submit();
}
}

</script>

<html>
<body>
<form name="form"  method="post">
<table>
<tr>
<td>ID</td>
<td><input type = "text" name = "id" maxlength ="10" size = "15"></td></tr>

<tr><td>비밀번호</td>
<td><input type = "password" name = "pwd" size = "15"></td></tr>

<tr><td>비밀번호 재입력</td>
<td><input type = "password" name = "pwd_re" size = "15"></td>
<td><input type = "button" value="확인" onClick="check()"></td></tr>

<tr><td>이름</td>
<td><input type = "text" name = "name" size = "15"></td></tr>

<tr><td>주소</td>
<td><input type = "text" name = "addr" size ="15"></td></tr>

<tr><td>성별</td>
<td><input type = "text" name = "sex" size = "15"></td></tr>

<tr><td>나이</td>
<td><input type = "text" name = "age" size ="15"></td></tr>

<tr><td>이메일</td>
<td><input type = "text" name = "email"></td></tr>
</table>
<tr><td><input type = "submit" value = "Submit" onclick="insert()"></td>
<td><input type = "reset" value = "Reset"></td></tr>
</form>
</body>
</html>
