require "test_helper"

class ChatsControllerTest < ActionDispatch::IntegrationTest
  include Devise::Test::IntegrationHelpers

  setup do
    @chat = chats(:one)
    @user1 = users(:one)
    @user2 = users(:two) 
    sign_in @user1
  end

  test "mostrar chats" do
    get chats_path
    assert_response :success
  end

  test "mostrar chat" do
    get chat_path(@chat)
    assert_response :success
  end

  test "crear chat con usuario y actividad sin chat previo" do
    assert_difference('Chat.count', 1) do
      post chats_path, params: { chat: { actividad_id: actividads(:two).id } }
    end
    assert_redirected_to chat_path(Chat.last)
  end

  test "no crear chat si ya existe entre los mismos usuarios y actividad" do
    # Asumimos que ya existe un chat entre @user_one y el creador de la actividad
    Chat.create!(actividad_id: actividads(:one).id, user1: @user1, user2: @user2)
    assert_no_difference('Chat.count') do
      post chats_path, params: { chat: { actividad_id: actividads(:one).id } }
    end
    assert_redirected_to chat_path(Chat.between_users(@user1, @user2).first)
  end

  test "borrar chat" do
    assert_difference('Chat.count', -1) do
      delete chat_path(@chat)
    end
    assert_redirected_to chats_path
  end
end
