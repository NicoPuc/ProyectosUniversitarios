require "test_helper"

class MessagesControllerTest < ActionDispatch::IntegrationTest
  include Devise::Test::IntegrationHelpers

  setup do
    @chat = chats(:one)
    @user_one = users(:one)
    sign_in @user_one
  end

  test "crear mensaje en un chat" do
    assert_difference('Message.count', 1) do
      post chat_messages_path(@chat), params: { message: { content: 'Nuevo mensaje', chat_id: @chat.id } }
    end
    assert_redirected_to chat_path(@chat)
  end
end
