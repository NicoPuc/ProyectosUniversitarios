require "test_helper"

class UsersControllerTest < ActionDispatch::IntegrationTest
  setup do
    @user = users(:one)
    
  end

  test "obtener usuario" do
    get new_user_registration_path
    assert_response :success
  end

  test "crear usuario" do
    assert_difference('User.count') do
      post user_registration_path, 
           params: { user: { email: 'new@prueba.com',name: 'dummytester', description: 'soy un dummy', phone: '12345', 
password: 'password123', password_confirmation: 'password123' } }
    end
    assert_redirected_to root_path
  end

  test "editar" do
    sign_in @user
    get edit_user_registration_path
    assert_response :success
  end

  test "actualizar usuario" do
    sign_in @user
    patch user_registration_path, 
          params: { user: { email: @user.email, current_password: 'prueba1234', password: 'newpassword123', 
password_confirmation: 'newpassword123' } }
    assert_redirected_to root_path
  end

  test "should destroy user" do
    sign_in @user
    assert_difference('User.count', -1) do
      delete user_registration_path
    end
    assert_redirected_to root_path # O ajusta según tu redirección esperada
  end
end
