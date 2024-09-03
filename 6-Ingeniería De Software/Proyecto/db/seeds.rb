admin_user = User.create!(
  name: 'Adminsoftware', 
  email: 'admin@uc.cl',
  password: 'claveadmin', 
  phone: '133',
  updating_password: true # Asegúrate de manejar este atributo según tu lógica de validación
)

Admin.create!(user: admin_user)