<html>
<head>
<link rel="stylesheet" href="http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css">
<script src="http://code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js"></script>
</head>
<body style="background-color:#333;">

	<?php 
	if(!isset($decode_data2[0]["orcid-profile"]["orcid-bio"]["contact-details"]["email"][0]["value"]))
		{ ?>
			<!-- Orcid getmail modal -->
<div class="modal  bs-example-modal-sm"  id= "orcidmail" tabindex="-1" role="dialog" aria-labelledby="mySmallModalLabel" aria-hidden="true">
  <div id="signup-dialog" class="modal-dialog modal-sm altmetricdiv">
    <div class="modal-content">
      <div class="modal-header"> Dear <b>User</b>, Your Orcid email seems private, Please enter your orcid email below and submit.
      
       </div>
            
<div class="modal-body" style="text-align: center;"> 
	<div class="form-group">
        <label for="email1" class="control-label col-xs-2">Orcid Email</label>
         <div class="col-xs-10 text-center">
        <input class="form-control" type="text" id="resetemail" name = "resetemail"/></div></div>
	<div class="text-center" style="padding-top:5px;"> <a style="display: block;" href="javascript:void(0);" id="orcidLogin"> <img src="images/Submit_button.gif"  /> </a></div>
	</div>
</div>
</div></div>
<script>
 $('#orcidmail').show();
$('#orcidLogin').click(function() {
	//alert("hello");
	//alert($("#resetemail").val());
	var email_address = $("#resetemail").val();
	alert(email_address)
	$.ajax({
				url: 'orcidLogin.php',
				method: 'GET',
				data: { email: email_address},
				success: function(data) {
					alert("Okay");
					console.log(data);
					
					if(data.trim().substring(0,12)!= "It seems you")
					{
					window.location="http://localhost/drupal";
					//window.opener.location.reload();
					window.close();
					}else{
					alert(data.trim());
				
					}
					 // window.location="search_new.php";
					
				},
				error: function(data) {
					console.log("Error with Orcid");
					//callback(data);
					//$("#spinner").hide();
				}
			});
	
});
</script>
		<?php }else{ ?>
        <script>
    </script>
   <?php } ?>
</body>

</html>



<?php // echo $UserId;?>
