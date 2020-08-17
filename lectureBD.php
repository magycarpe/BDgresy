<!DOCTYPE html>
<html>
    <head>
        <style>
            table {
                border-collapse: collapse;
                width: 100%;
                color: #1f5380;
                font-family: monospace;
                font-size: 20px;
                text-align: left;
            }
            th {
                background-color: #1f5380;
                color: white;
            }
            tr:nth-child(even) {background-color: #f2f2f2}
        </style>
    </head>
    <?php
        //Creates new record as per request
        //Connect to database
        $hostname = "127.0.0.1";        //example = localhost or 192.168.0.0
        $username = "site";        //example = root
        $password = "site";
        $dbname = "site";
        // Create connection
        $conn = mysqli_connect($hostname, $username, $password, $dbname);
        // Check connection
        if (!$conn) {
            die("Connection failed !!!");
        }
    ?>
    <body>
    	<div class="titre">
    		<h1 class="title">Base de données de remplissage</h1>
    	</div>
    	<p>
    	Voici l'état du parc :
    	</p>

        <table class="tableau">
            <tr>
                <th>point</th>
                <th>niveau</th>
                <th>date</th>
            </tr>
            <?php
                $table = mysqli_query($conn, "SELECT point, niveau, date, FROM rempli");
                while($row = mysqli_fetch_array($table))
                {
            ?>
            <tr>
                <td><?php echo $row["point"]; ?></td>
                <td><?php echo $row["niveau"]; ?></td>
                <td><?php echo $row["date"]; ?></td>
            </tr>
            <?php
                }
            ?>
        </table>
        <p>
        Points à récupérer :
        </p>
        <table class="tableau">
        	<tr>
       		<th>point</th>
       		<th>lieu</th>
               	<th>niveau</th>
               </tr>
        	<?php
                $table = mysqli_query($conn, "SELECT rempli.point, adresse.lieu, rempli.niveau, FROM rempli JOIN adresse ON adresse.point=rempli.point WHERE rempli.niveau>75");
                while($row = mysqli_fetch_array($table))
                {
            ?>
            <tr>
                <td><?php echo $row["point"]; ?></td>
                <td><?php echo $row["lieu"]; ?></td>
                <td><?php echo $row["niveau"]; ?></td>
            </tr>
            <?php
                }
            ?>
         </table>
    </body>
</html>
