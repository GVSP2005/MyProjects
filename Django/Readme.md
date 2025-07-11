# 🎓 Student Management System
## 📖 Description

    Django based web application to store student records.
## ✨ Features

    👩‍🎓 View a list of students with details like name, roll number, branch, and email.

    🔒 Admin interface to add, edit, and delete student records securely.

    📱 Responsive UI designed using Bootstrap 5.

    🎨 Customized Django admin with Jazzmin for enhanced user experience.

## 🚀 Future Plans

    🔐 Add user authentication: login/logout functionality.

    👩‍💻 Implement separate student and faculty login portals with role-based access.

    📝 Allow student self-registration through a dedicated form.

    🧑‍🏫 Enable faculty to update student records.

    🔄 Add password reset and profile management features.

    ☁️ Deploy the application to a cloud platform.

## ⚙️ Setup & Installation
🧰 **Prerequisites**

    🐍 Python 3.8 or above

    🥚 Virtual environment (recommended)

## Getting Started

## **1. Clone the Repository**
git clone https://github.com/yourusername/student-management-system.git  
cd student-management-system

## **2. Create and Activate a Virtual Environment**
python3 -m venv venv  
source venv/bin/activate      # On Windows: venv\Scripts\activate

## **3. Install Dependencies**
pip install -r requirements.txt

## **4. Apply Migrations**
python manage.py makemigrations    # Optional if migrations already exist  
python manage.py migrate

## **5. Create a Superuser**
python manage.py createsuperuser

## **6. Run the Development Server**
python manage.py runserver

## **Access the Application**

### **Student list page:**  
na http://127.0.0.1:8000/students/

### **Admin panel:**  
na http://127.0.0.1:8000/admin/
