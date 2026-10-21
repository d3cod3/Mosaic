

<html>

<header></header>

<body>

</body>

<footer>
<?php

if (isset($_GET['r']) && is_string($_GET['r'])) {
    $data = filter_input(INPUT_GET, 'r', FILTER_SANITIZE_SPECIAL_CHARS);
}

if ($data !== null || $data !== false) {
    $data = trim($data);              // Strip unnecessary characters (extra space, tab, newline)
    $data = stripslashes($data);      // Remove backslashes (\)
    $data = htmlspecialchars($data);  // save as HTML escaped code

    echo    '<script type="text/javascript">
                var form = document.createElement("form");
                form.target = "_self";
                form.method = "POST";
                form.action = "https://mosaic.d3cod3.org/reference.php";
                form.style.display = "none";

                var input = document.createElement("input");
                input.type = "hidden";
                input.name = "r";
                input.value = "'.$data.'";
                form.appendChild(input);

                document.body.appendChild(form);
                form.submit();
                document.body.removeChild(form);
            </script>';

}   




?>
</footer>

</html>