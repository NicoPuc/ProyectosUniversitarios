require "test_helper"

class ActividadsControllerTest < ActionDispatch::IntegrationTest
  test "mostrar actividades" do
    get actividads_path
    assert_response :success
  end

  test "mostrar detalle de actividad 1" do
    actividad = actividads(:one)
    get actividad_path(actividad)
    assert_response :success
  end

  test "mostrar detalle de actividad 2" do
    actividad = actividads(:two)
    get actividad_path(actividad)
    assert_response :success
  end

  test "nueva actividad" do
    user = users(:one)
    sign_in user
    get new_actividad_path
    assert_response :success
    assert_select 'form'
  end

  test "editar actividad 1" do
    user = users(:one)
    actividad = actividads(:two)
    sign_in user
    get edit_actividad_path(actividad)
    assert_response :success
    assert_select 'form'
  end

  test "editar actividad 2" do
    user = users(:two)
    actividad = actividads(:one)
    sign_in user
    get edit_actividad_path(actividad)
    assert_response :success
    assert_select 'form'
  end

  test "editar actividad 1 desde admin" do
    admin = users(:three)
    actividad = actividads(:one)
    sign_in admin
    get edit_actividad_path(actividad)
    assert_response :success
    assert_select 'form'
  end

  test "editar actividad 2 desde admin" do
    admin = users(:three)
    actividad = actividads(:two)
    sign_in admin
    get edit_actividad_path(actividad)
    assert_response :success
    assert_select 'form'
  end

  test "eliminar actividad desde admin" do
    admin = users(:three)
    sign_in admin
    assert_difference('Actividad.count', -1) do
      delete actividad_path(actividads(:one))
    end
    assert_redirected_to actividads_path
  end

  test "crear actividad" do
    user = users(:one)
    sign_in user
    assert_difference('Actividad.count') do
      post actividads_path, 
           params: { actividad: { titulo: "test new product", cantidad_personas: 10, precio: 2000, 
fecha: "2024-10-15" } }
    end
    assert_redirected_to actividads_path
  end
end
