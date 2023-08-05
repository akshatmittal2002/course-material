import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.text.*;
import javax.swing.*;
import java.util.*;

class Form{
    private static int numLine; // Number of lines in database
    private static FileWriter database; // File Writer to write to the database
    // All the required components of the form
    private static JFrame f;
    private JLabel nameL, dobL, genderL, emailL, passwordL, branchL, mobileL, mathsMarksL, physicsMarksL, chemistryMarksL, percentageL;
    private JTextField nameT, emailT, mobileT, mathsMarksT, physicsMarksT, chemistryMarksT, percentageT;
    private JFormattedTextField dobT;
    private JRadioButton male, female;
    private ButtonGroup g1;
    private JPasswordField passwordT;
    private JComboBox<String> branchT;
    private String[] branches;
    private JButton calculate, submit;
    private JLabel nameError, dobError, genderError, emailError, passwordError, mobileError, mathsMarksError, physicsMarksError, chemistryMarksError, percentageError;
    
    // Function to check if the date of birth is valid
    private boolean checkDob(){
        String dob = dobT.getText();
        int day = Integer.parseInt(dob.substring(0, 2));
        int month = Integer.parseInt(dob.substring(3, 5));
        int year = Integer.parseInt(dob.substring(6, 10));
        if(day > 31 || day < 1 || month > 12 || month < 1 || year > 9999){
            return false;
        }
        return true;
    }

    // Function to check if all the fields entered are valid
    private boolean checkValid(){
        // Validity of name
        if(nameT.getText().length() == 0){
            nameError.setVisible(true);
            return false;
        }
        // Validity of date of birth
        if(dobT.getText().length() != 10 || dobT.getText().length() == 0 || !checkDob()){
            dobError.setVisible(true);
            return false;
        }
        // Validity of gender
        if(g1.getSelection() == null){
            genderError.setVisible(true);
            return false;
        }
        // Validity of email
        if(emailT.getText().length() == 0 || !emailT.getText().contains("@") || !emailT.getText().contains(".")){
            emailError.setVisible(true);
            return false;
        }
        // Validity of password
        if(passwordT.getPassword().length == 0){
            passwordError.setVisible(true);
            return false;
        }
        // Validity of mobile number
        if(mobileT.getText().length() == 0){
            mobileError.setVisible(true);
            return false;
        }
        // Validity of marks
        if(percentageT.getText().length() == 0){
            percentageError.setVisible(true);
            return false;
        }
        return true;
    }

    // Function to reset the form to original state after submission
    private void resetForm(){
        nameT.setText("");
        dobT.setText("");
        g1.clearSelection();
        emailT.setText("");
        passwordT.setText("");
        branchT.setSelectedIndex(0);
        mobileT.setText("");
        mathsMarksT.setText("");
        physicsMarksT.setText("");
        chemistryMarksT.setText("");
        percentageT.setText("");
        nameError.setVisible(false);
        dobError.setVisible(false);
        genderError.setVisible(false);
        emailError.setVisible(false);
        passwordError.setVisible(false);
        mobileError.setVisible(false);
        mathsMarksError.setVisible(false);
        physicsMarksError.setVisible(false);
        chemistryMarksError.setVisible(false);
        percentageError.setVisible(false);
    }

    // Form Constructor
    Form(){
        // Frame
        f = new JFrame("Registration Desk");
        f.setSize(800, 800);
        f.setLayout(null);

        // Name Field
        nameL = new JLabel("Name:"); // Label
        nameT = new JTextField(); // Text
        nameL.setBounds(50, 50, 100, 30); // Position of Label on the frame
        nameT.setBounds(200, 50, 200, 30); // Position of Text on the frame
        nameError = new JLabel("*Please Enter valid Name"); // Error Label
        nameError.setBounds(420, 50, 250, 30); // Position of Error Label on the frame
        nameError.setVisible(false); // Initially the error label is not visible
        nameError.setForeground(Color.red); // Color of the text in error label
        // Key Listener to check if the name entered is valid, i.e. only alphabets and spaces are allowed
        nameT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z') || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE) || (c == KeyEvent.VK_SPACE))){
                    nameError.setVisible(true);
                    e.consume();
                }
                else{
                    nameError.setVisible(false);
                }
            }
        });
        // Add components to the frame
        f.add(nameL);
        f.add(nameT);
        f.add(nameError);

        // DOB Field
        dobL = new JLabel("DOB:");
        DateFormat df = new SimpleDateFormat("dd/MM/yyyy"); // Date Format for the text field
        dobT = new JFormattedTextField(df);
        dobError = new JLabel("*Please Enter valid DOB in DD/MM/YYYY format");
        dobL.setBounds(50, 100, 100, 30);
        dobT.setBounds(200, 100, 200, 30);
        dobError.setBounds(420, 100, 300, 30);
        dobError.setVisible(false);
        dobError.setForeground(Color.red);
        // Key Listener to check if the date of birth entered is valid, i.e. only numbers and / are allowed
        dobT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= '0') && (c <= '9') || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE) || (c == KeyEvent.VK_SLASH))){
                    dobError.setVisible(true);
                    e.consume();
                }
                else{
                    dobError.setVisible(false);
                }
            }
        });
        f.add(dobL);
        f.add(dobT);
        f.add(dobError);

        // Gender Field
        genderL = new JLabel("Gender:");
        male = new JRadioButton("Male");
        female = new JRadioButton("Female");
        genderL.setBounds(50, 150, 100, 30);
        male.setBounds(200, 150, 100, 30);
        female.setBounds(300, 150, 100, 30);
        g1 = new ButtonGroup(); // Grouping the radio buttons so that only one can be selected at a time
        genderError = new JLabel("*Please select your Gender");
        genderError.setBounds(420, 150, 250, 30);
        genderError.setVisible(false);
        genderError.setForeground(Color.red);
        male.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                genderError.setVisible(false);
            }
        });
        female.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                genderError.setVisible(false);
            }
        });
        g1.add(male);
        g1.add(female);
        f.add(genderL);
        f.add(male);
        f.add(female);
        f.add(genderError);

        // Email Field
        emailL = new JLabel("Email:");
        emailT = new JTextField();
        emailL.setBounds(50, 200, 100, 30);
        emailT.setBounds(200, 200, 200, 30);
        emailError = new JLabel("*Please Enter valid Email");
        emailError.setBounds(420, 200, 250, 30);
        emailError.setVisible(false);
        emailError.setForeground(Color.red);
        emailT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                emailError.setVisible(false);
            }
        });
        f.add(emailL);
        f.add(emailT);
        f.add(emailError);

        // Password Field
        passwordL = new JLabel("Create Password:");
        passwordT = new JPasswordField();
        passwordError = new JLabel("*Please Enter valid Password");
        passwordL.setBounds(50, 250, 100, 30);
        passwordT.setBounds(200, 250, 200, 30);
        passwordError.setBounds(420, 250, 250, 30);
        passwordError.setVisible(false);
        passwordError.setForeground(Color.red);
        passwordT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                passwordError.setVisible(false);
            }
        });
        f.add(passwordL);
        f.add(passwordT);
        f.add(passwordError);

        // Mobile Number Field
        mobileL = new JLabel("Mobile Number:");
        mobileT = new JTextField();
        mobileL.setBounds(50, 300, 100, 30);
        mobileT.setBounds(200, 300, 200, 30);
        mobileError = new JLabel("*Please Enter valid 10 digit Mobile Number");
        mobileError.setBounds(420, 300, 250, 30);
        mobileError.setVisible(false);
        mobileError.setForeground(Color.red);
        // Key Listener to check if the mobile number entered is valid, i.e. only numbers are allowed
        mobileT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= '0') && (c <= '9') || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))){
                    mobileError.setVisible(true);
                    e.consume();
                }
                else{
                    mobileError.setVisible(false);
                }
            }
        });
        f.add(mobileL);
        f.add(mobileT);
        f.add(mobileError);

        // Branch Field
        branchL = new JLabel("Desired Branch:");
        branches = new String[]{"CSE", "ME", "EE", "ET", "CE"}; // List of branches
        branchT = new JComboBox<String>(branches); // Combo Box to select the branch using drop down menu
        branchL.setBounds(50, 350, 100, 30);
        branchT.setBounds(200, 350, 200, 30);
        f.add(branchL);
        f.add(branchT);

        // Maths Marks Field
        mathsMarksL = new JLabel("Marks in Math:");
        mathsMarksT = new JTextField();
        mathsMarksError = new JLabel("*Please Enter valid Marks <= 100");
        mathsMarksL.setBounds(50, 400, 100, 30);
        mathsMarksT.setBounds(200, 400, 200, 30);
        mathsMarksError.setBounds(420, 400, 250, 30);
        mathsMarksError.setVisible(false);
        mathsMarksError.setForeground(Color.red);
        f.add(mathsMarksL);
        f.add(mathsMarksT);
        f.add(mathsMarksError);
        // Key Listener to check if the marks entered is valid, i.e. only numbers are allowed
        mathsMarksT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= '0') && (c <= '9') || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))){
                    mathsMarksError.setVisible(true);
                    e.consume();
                }
                else{
                    mathsMarksError.setVisible(false);
                }
            }
        });

        // Physics Marks Field
        physicsMarksL = new JLabel("Marks in Physics:");
        physicsMarksT = new JTextField();
        physicsMarksError = new JLabel("*Please Enter valid Marks <= 100");
        physicsMarksL.setBounds(50, 450, 100, 30);
        physicsMarksT.setBounds(200, 450, 200, 30);
        physicsMarksError.setBounds(420, 450, 250, 30);
        physicsMarksError.setVisible(false);
        physicsMarksError.setForeground(Color.red);
        f.add(physicsMarksL);
        f.add(physicsMarksT);
        f.add(physicsMarksError);
        // Key Listener to check if the marks entered is valid, i.e. only numbers are allowed
        physicsMarksT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= '0') && (c <= '9') || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))){
                    physicsMarksError.setVisible(true);
                    e.consume();
                }
                else{
                    physicsMarksError.setVisible(false);
                }
            }
        });

        // Chemistry Marks Field
        chemistryMarksL = new JLabel("Marks in Chemistry:");
        chemistryMarksT = new JTextField();
        chemistryMarksError = new JLabel("*Please Enter valid Marks <= 100");
        chemistryMarksL.setBounds(50, 500, 150, 30);
        chemistryMarksT.setBounds(200, 500, 200, 30);
        chemistryMarksError.setBounds(420, 500, 250, 30);
        chemistryMarksError.setVisible(false);
        chemistryMarksError.setForeground(Color.red);
        f.add(chemistryMarksL);
        f.add(chemistryMarksT);
        f.add(chemistryMarksError);
        // Key Listener to check if the marks entered is valid, i.e. only numbers are allowed
        chemistryMarksT.addKeyListener(new KeyAdapter() {
            public void keyTyped(KeyEvent e) {
                char c = e.getKeyChar();
                if (!((c >= '0') && (c <= '9') || (c == KeyEvent.VK_BACK_SPACE) || (c == KeyEvent.VK_DELETE))){
                    chemistryMarksError.setVisible(true);
                    e.consume();
                }
                else{
                    chemistryMarksError.setVisible(false);
                }
            }
        });

        // Percentage Field
        percentageL = new JLabel("Percentage:");
        percentageT = new JTextField();
        percentageL.setBounds(50, 550, 100, 30);
        percentageT.setBounds(200, 550, 200, 30);
        percentageT.setEditable(false); // Percentage field is not editable
        percentageT.setBorder(BorderFactory.createLineBorder(Color.black));
        percentageError = new JLabel("*Please Calculate Percentage");
        percentageError.setBounds(200, 580, 250, 30);
        percentageError.setVisible(false);
        percentageError.setForeground(Color.red);
        f.add(percentageL);
        f.add(percentageT);
        f.add(percentageError);

        // Calculate Percentage Button
        calculate = new JButton("Calculate Percentage");
        calculate.setBounds(450, 550, 200, 30);
        // Action Listener to calculate the percentage
        calculate.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                percentageError.setVisible(false);
                // Checking if the marks fields are empty
                if(mathsMarksT.getText().length() == 0){
                    mathsMarksError.setVisible(true);
                    return;
                }
                else {
                    mathsMarksError.setVisible(false);
                }
                int maths = Integer.parseInt(mathsMarksT.getText()); // Converting the marks to integer
                // Checking if the marks entered is valid
                if(maths < 0 || maths > 100) {
                    mathsMarksError.setVisible(true);
                    return;
                }
                else {
                    mathsMarksError.setVisible(false);
                }
                if(physicsMarksT.getText().length() == 0){
                    physicsMarksError.setVisible(true);
                    return;
                }
                else {
                    physicsMarksError.setVisible(false);
                }
                int physics = Integer.parseInt(physicsMarksT.getText());
                if(physics < 0 || physics > 100) {
                    physicsMarksError.setVisible(true);
                    return;
                }
                else {
                    physicsMarksError.setVisible(false);
                }
                if(chemistryMarksT.getText().length() == 0){
                    chemistryMarksError.setVisible(true);
                    return;
                }
                else {
                    chemistryMarksError.setVisible(false);
                }
                int chemistry = Integer.parseInt(chemistryMarksT.getText());
                if(chemistry < 0 || chemistry > 100) {
                    chemistryMarksError.setVisible(true);
                    return;
                }
                else {
                    chemistryMarksError.setVisible(false);
                }
                // Calculating the percentage
                int total = maths + physics + chemistry;
                double percentage = (total / 3.0);
                // Formatting the percentage to 2 decimal places
                Formatter fo = new Formatter();
                fo.format("%.2f", percentage);
                percentageT.setText(String.valueOf(fo) + " %");
            }
        });
        f.add(calculate);

        // Submit Button
        submit = new JButton("Register");
        submit.setBounds(250, 650, 300, 30);
        // Action Listener to write the data to the database
        submit.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Checking if the form is valid
                if(!checkValid()){
                    return;
                }
                // Creating the entry to be written to the database
                String entry = (numLine + 1) + " | ";
                entry += nameT.getText() + " | ";
                entry += dobT.getText() + " | ";
                if(male.isSelected()) entry += "Male | ";
                else if(female.isSelected()) entry += "Female | ";
                entry += emailT.getText() + " | ";
                entry += new String(passwordT.getPassword()) + " | ";
                entry += mobileT.getText() + " | ";
                entry += branchT.getSelectedItem() + " | ";
                entry += mathsMarksT.getText() + " | ";
                entry += physicsMarksT.getText() + " | ";
                entry += chemistryMarksT.getText() + " | ";
                entry += percentageT.getText() + " |\n";
                // Writing the entry to the database
                try{
                    database.write(entry);
                    // Displaying success message on dialog box
                    JOptionPane.showMessageDialog(f, "Registration Successful", "Success", JOptionPane.INFORMATION_MESSAGE);
                    // Flushing the database file to save the data
                    database.flush();
                    // Resetting the form
                    resetForm();
                    // Increment the number of lines in the database file
                    numLine += 1;
                }catch(IOException e1){
                    // Displaying error message on dialog box, if any error occurs
                    JOptionPane.showMessageDialog(f, "Registration Failed:\n" + e1, "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        f.add(submit);

        f.setVisible(true);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    // Main Function
    public static void main(String[] args){
        // Read Database File to get number of lines
        File fi = new File("Database.txt");
        numLine = 0;
        if(fi.exists()){
            FileReader fr = null;
            try{
                fr = new FileReader(fi);
                BufferedReader br = new BufferedReader(fr);
                // Count number of lines in the database file
                String line;
                while((line = br.readLine()) != null){
                    numLine = Integer.parseInt(line.split(" |")[0]);
                }
                fr.close();
            }catch(IOException e){
                // If any error occurs, display error message and exit
                System.out.println("Error: " + e);
                return;
            }
        }
        // Open Database File to write
        try{
            database = new FileWriter("Database.txt", true);
        }catch(IOException e){
            // If any error occurs, display error message and exit
            System.out.println("Error: " + e);
            return;
        }
        // Create new Form
        new Form();

        // Close Database File on Window Close
        f.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                if(database != null){
                    try{
                        database.close();
                    }catch(IOException e1){
                        System.out.println("Error: " + e1);
                        return;
                    }
                }
            }
        });
    }
}