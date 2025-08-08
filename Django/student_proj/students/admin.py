from django.contrib import admin
from .models import Student
# Register your models here.
@admin.register(Student)
class StudentAdmin(admin.ModelAdmin):
    list_display = ('name', 'roll_number', 'branch', 'email', 'created_at')
    search_fields = ('name', 'roll_number')
    list_filter = ('branch',)
    ordering = ('branch','roll_number',)
    readonly_fields = ('created_at',)
