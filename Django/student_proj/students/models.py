from django.db import models

# Create your models here.
class Student(models.Model):
    name=models.CharField(max_length=100)
    roll_number=models.IntegerField(unique=True)
    branch=models.CharField(max_length=50)
    email=models.EmailField()
    created_at=models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.name} - {self.roll_number}"
    